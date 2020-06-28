#include "LP_Entry.h"

// Constructor
LP_Entry::LP_Entry(string input, bool stolen, bool wanted, bool weapon, bool known_crim) : _stolen(stolen), _wanted(wanted), _weapon(weapon), _known_criminal(known_crim) {
    this->setNumber(input);
}

// Destructor
LP_Entry::~LP_Entry() { }

// Evaluates, if a stop of this vehicle could be risky
bool LP_Entry::evalRiskyStop() {
    return this->_weapon || this->_known_criminal;
}

// Evalautes, if a stop is required
bool LP_Entry::evalStopRequried() {
    return this->_stolen || this->_wanted;
}

// Getter
bool LP_Entry::getStolenState() {
    return _stolen;
}

bool LP_Entry::getWantedState() {
    return _wanted;
}

bool LP_Entry::getWeaponState() {
    return _weapon;
}

bool LP_Entry::getKnownCriminalState() {
    return _known_criminal;
}

// Setter
void LP_Entry::setStolenState(bool stolen) {
    _stolen = stolen;
}
void LP_Entry::setWantedState(bool wanted) {
    _wanted = wanted;
}
void LP_Entry::setWeaponState(bool weapon) {
    _weapon = weapon;
}
void LP_Entry::setKnownCriminalState(bool known_crim) {
    _known_criminal = known_crim;
}