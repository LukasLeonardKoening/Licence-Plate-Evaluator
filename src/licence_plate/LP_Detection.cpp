#include "LP_Detection.h"

// Constructor
LicencePlateDetection::LicencePlateDetection(string input, double acc) : accuracy(acc) { 
    this->setNumber(input);
}

// Getter and setter functions
void LicencePlateDetection::setAccuracy(double acc) {
    this->accuracy = acc;
}

double LicencePlateDetection::getAccuracy() {
    return this->accuracy;
}