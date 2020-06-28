#include "LP_Evaluator.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

/* MessageQueue Definitions */

template<typename T> T MessageQueue<T>::receive() {
    // Protect work by a unique lock
    std::unique_lock<std::mutex> unique_lock(_mutex);

    // Wait until message is available
    _cond.wait(unique_lock, [this] { return !_queue.empty(); });

    // Return message (using move semantics)
    auto msg = std::move(_queue.back());
    _queue.erase(_queue.end());
    return msg;
}

template<typename T> void MessageQueue<T>::send(T &&msg) {
    // Protect work by a lock guard
    std::lock_guard<std::mutex> lock(_mutex);

    // Add message to queue
    _queue.push_back(std::move(msg));

    // Notify condition variable
    _cond.notify_one();
}


/* LicencePlateEvaluator definitions */

// Constructor
LicencePlateEvaluator::LicencePlateEvaluator(string database_file) {
    _results = std::make_shared<MessageQueue<LicencePlateEvaluationResult>>();
    threads.emplace_back(std::thread(&LicencePlateEvaluator::update, this, database_file));
}

// Destructor
LicencePlateEvaluator::~LicencePlateEvaluator() {
    std::for_each(threads.begin(), threads.end(), [](std::thread &t) {
        t.join();
    });
}

// Creates thread for the update
void LicencePlateEvaluator::updateDatabase(string database_file) {
    threads.emplace_back(std::thread(&LicencePlateEvaluator::update, this, database_file));
}

// Update the database with new licence plates from file
void LicencePlateEvaluator::update(string database_file) {
    // Protect operation with a lock
    std::lock_guard<std::mutex> database_lock(mutex_database);

    // Usage of a mutex for output protection
    mutex_cout.lock();
    std::cout << "[INFO]: Updating database..." << std::endl;
    mutex_cout.unlock();

    // Clean up database
    database.clear();

    // Declare needed variables
    std::ifstream databaseIN;
    string line;
    int counter = 0;

    // Open filestream and check the operation
    databaseIN.open(database_file);
    if (!databaseIN) {
        mutex_cout.lock();
        std::cerr << "[ERROR]: Database could not be opened!" << std::endl;
        mutex_cout.unlock();
        return;
    }
    // Read database line by line
    while(getline(databaseIN,line)) {
        // Lineformat: "XXX-XX-XXXX 0 0 0 0"
        // LP number, stolen, wanted, weapon, criminal
        std::vector<string> components;
        std::stringstream inputstream(line);

        // Extract components
        string temp;
        while (inputstream >> temp) {
            components.push_back(temp);
        }

        // Save data to local database
        LP_Entry entry(components[0], false, false, false, false);
        if (components[1] == "1") {
            entry.setStolenState(true);
        }
        if (components[2] == "1") {
            entry.setWantedState(true);
        }
        if (components[3] == "1") {
            entry.setWeaponState(true);
        }
        if (components[4] == "1") {
            entry.setKnownCriminalState(true);
        }
        this->database.push_back(entry);
        counter++;
    }
    mutex_cout.lock();
    std::cout << "[INFO]: " << counter << " vehicles added from database." << std::endl;
    std::cout << "[INFO]: Database successfully updated!" << std::endl;
    mutex_cout.unlock();
}

// Create thread for each evaluation
void LicencePlateEvaluator::evaluateLicencePlate(LicencePlateDetection lp) {
    threads.emplace_back(std::thread(&LicencePlateEvaluator::evaluate, this, lp));
}

// Evaluate a detected licence plate
void LicencePlateEvaluator::evaluate(LicencePlateDetection lp) {
    // Check if accuracy/certainty of detection is high enough
    if (lp.getAccuracy() >= 0.75) {
        // Check database for licence plate
        LicencePlateEvaluationResult result(lp, UNKNOWN);

        mutex_database.lock();
        for (int i=0; i < database.size(); i++) {
            // if licence plate is in database
            if (database[i].getTotalNumber() == lp.getTotalNumber()) {
                // Check if stop is required
                if (database[i].evalStopRequried()) {
                    result.setState(STOP_NOTRISKY);
                    // Check if stop could be risky
                    if (database[i].evalRiskyStop()) {
                        result.setState(STOP_RISKY);
                    }
                } else {
                    result.setState(NORMAL);
                }
            }
        }
        mutex_database.unlock();
        // Add result to the _result message queue
        auto f_queue = std::async(std::launch::async, &MessageQueue<LicencePlateEvaluationResult>::send, _results, std::move(result));
        f_queue.wait();
    } else {
        mutex_cout.lock();
        std::cout << "[INFO]: Accurcy of " << lp.getTotalNumber() << " too low to evaluate." << std::endl;
        mutex_cout.unlock();

        // Add result to the _result message queue
        LicencePlateEvaluationResult result(lp, UNKNOWN);
        auto f_queue = std::async(std::launch::async, &MessageQueue<LicencePlateEvaluationResult>::send, _results, std::move(result));
        f_queue.wait();
    }
}

// Create thread to run evaluator not in main thread
void LicencePlateEvaluator::runEvaluator() {
    threads.emplace_back(std::thread(&LicencePlateEvaluator::run, this));
}

// Run the Evaluator and wait for results
void LicencePlateEvaluator::run() {
    while(true) {
        // Check results every 1/10th second
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        auto result = this->_results->receive();
        mutex_cout.lock();
        switch (result.getState()) {
            case STOP_NOTRISKY:
                std::cout << "[ATTENTION]: Vehicle with licence plate '" << result.getDetection().getTotalNumber() << "' is marked as stolen or wanted! Risk of stop is low!";
                break;
            case STOP_RISKY:
                std::cout << "[ATTENTION]: Vehicle with licence plate '" << result.getDetection().getTotalNumber() << "' is marked as stolen or wanted! Risk of stop is HIGH!";
                break;
            case NORMAL:
                std::cout << "[INFO]: Vehicle with licence plate '" << result.getDetection().getTotalNumber() << "' is known but not marked.";
                break;
            case UNKNOWN:
                std::cout << "[INFO]: Vehicle with licence plate '" << result.getDetection().getTotalNumber() << "' is unknown.";
                break;
            default:
                break;
        }
        std::cout << std::endl;
        mutex_cout.unlock();
    }
}