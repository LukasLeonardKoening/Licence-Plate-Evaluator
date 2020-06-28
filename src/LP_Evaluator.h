#ifndef LP_EVALUATOR
#define LP_EVALUATOR

#include <vector>
#include <future>
#include <mutex>
#include <deque>
#include "licence_plate/LP_Detection.h"
#include "licence_plate/LP_Entry.h"
#include "licence_plate/LP_EvalResult.h"

using std::vector;

// Message queue template
template <class T> class MessageQueue {
    public:
        T receive();
        void send(T &&msg);

    private:
        std::mutex _mutex;
        std::condition_variable _cond;
        std::deque<T> _queue;
};

class LicencePlateEvaluator {
    public:
        // Constructor & Destructor
        LicencePlateEvaluator(string database_file);
        ~LicencePlateEvaluator();

        // Functionality
        void runEvaluator();
        void evaluateLicencePlate(LicencePlateDetection lp);
        void updateDatabase(string database_file);
    private:
        // Private functions
        void run();
        void update(string database_file);
        void evaluate(LicencePlateDetection lp);

        // Variables
        std::shared_ptr<MessageQueue<LicencePlateEvaluationResult>> _results;
        vector<LP_Entry> database;
        vector<std::thread> threads;
        std::mutex mutex_database;
        std::mutex mutex_cout;

};

#endif