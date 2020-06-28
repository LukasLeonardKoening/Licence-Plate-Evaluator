#include "LP_EvalResult.h"

// Constructor
LicencePlateEvaluationResult::LicencePlateEvaluationResult(LicencePlateDetection detect, LicencePlateState st) : _detection(detect), _state(st) { }

// Getter functions
LicencePlateDetection LicencePlateEvaluationResult::getDetection() {
    return _detection;
}

LicencePlateState LicencePlateEvaluationResult::getState() {
    return _state;
}

// Setter functions
void LicencePlateEvaluationResult::setState(LicencePlateState state) {
    _state = state;
}