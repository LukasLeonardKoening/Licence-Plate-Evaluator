#include "LicencePlate.h"

#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>

// Constructor
// INPUT: input = string with format XX-XX-XXXX
LicencePlate::LicencePlate(string input) {
    setNumber(input);
}

// Destructor
LicencePlate::~LicencePlate() { }

void LicencePlate::setNumber(string input) {
    std::vector<string> components;

    // Prepare input
    std::replace(input.begin(), input.end(), '-', ' ');
    std::stringstream inputstream(input);

    // Extract components
    string temp;
    while (inputstream >> temp) {
        components.push_back(temp);
    }

    // Save input to object
    this->city_code = components[0];
    this->char_combi = components[1];
    try {
        this->number_combi = std::stoi(components[2]);
    } catch (...) {
        std::cerr << "Number combination of licence plate must be a number!" << std::endl;
    }
}

// Getter functions
string const LicencePlate::getTotalNumber() {
    return this->city_code + "-" + this->char_combi + "-" + std::to_string(this->number_combi);
}

string LicencePlate::getCityCode() {
    return this->city_code;
}

string LicencePlate::getChars() {
    return this->char_combi;
}

int LicencePlate::getNumbers() {
    return this->number_combi;
}