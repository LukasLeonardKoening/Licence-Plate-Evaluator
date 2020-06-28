#include <iostream>

#include "licence_plate/LP_Detection.h"
#include "LP_Evaluator.h"

int main() {

    // Usage example

    // Init Evaluator
    LicencePlateEvaluator munich("../database/munich.txt");
    munich.runEvaluator();

    // Evaluate some licence plates
    LicencePlateDetection test1("M-AB-1666", 0.95);
    munich.evaluateLicencePlate(test1);
    LicencePlateDetection test2("B-AB-1665", 1.0);
    munich.evaluateLicencePlate(test2);
    LicencePlateDetection test3("M-AB-1664", 0.5);
    munich.evaluateLicencePlate(test3);
    LicencePlateDetection test4("M-AB-4242", 0.85);
    munich.evaluateLicencePlate(test4);

    // Update database of licence plates
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    munich.updateDatabase("../database/munich.txt");

    return 0;
}