#ifndef LP_ENTRY
#define LP_ENTRY

#include "LicencePlate.h"

class LP_Entry : public LicencePlate {
    public:
        // Constructor & Destructor
        LP_Entry(string input, bool stolen, bool wanted, bool weapon, bool known_crim);
        ~LP_Entry();

        // Functions
        bool evalRiskyStop();
        bool evalStopRequried();

        // Getter and setter
        bool getStolenState();
        bool getWantedState();
        bool getWeaponState();
        bool getKnownCriminalState();

        void setStolenState(bool stolen);
        void setWantedState(bool wanted);
        void setWeaponState(bool weapon);
        void setKnownCriminalState(bool known_crim);

    private:
        // Variables
        bool _stolen;
        bool _wanted;
        bool _weapon;
        bool _known_criminal;
};

#endif