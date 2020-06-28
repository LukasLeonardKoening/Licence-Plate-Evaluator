#ifndef LP_DETECTION
#define LP_DETECTION

#include "LicencePlate.h"

class LicencePlateDetection : public LicencePlate {

    public:
        // Constructor
        LicencePlateDetection(string input, double acc);

        // Getter and setter
        void setAccuracy(double acc);
        double getAccuracy();
    private:
        // Variables
        double accuracy;
};

#endif