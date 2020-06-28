#ifndef LP_EVALUATIONRESULT
#define LP_EVALUATIONRESULT

#include "LP_Detection.h"

// Enum for states of the detected licence plate
enum LicencePlateState { UNKNOWN, NORMAL, STOP_NOTRISKY, STOP_RISKY };

class LicencePlateEvaluationResult {
    public:
        // Constructor
        LicencePlateEvaluationResult(LicencePlateDetection detect, LicencePlateState st);

        // Getter and setter functions
        LicencePlateDetection getDetection();
        LicencePlateState getState();
        void setState(LicencePlateState state);

    private:
        // Variables
        LicencePlateDetection _detection;
        LicencePlateState _state; 
};

#endif