#ifndef LICENCE_PLATE
#define LICENCE_PLATE

#include <string>

using std::string;

class LicencePlate {
    public:
        // Constructor / Destructor
        LicencePlate(string input);
        LicencePlate() = default;
        ~LicencePlate();

        // Getter & setter functions
        void setNumber(string input);
        string const getTotalNumber();
        string getCityCode();
        string getChars();
        int getNumbers();
        
    private:
        // Variables
        string city_code;
        string char_combi;
        int number_combi;
};



#endif