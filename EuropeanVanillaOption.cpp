#include "EuropeanVanillaOption.h"

// Constructor
EuropeanVanillaOption::EuropeanVanillaOption(double expiry, double strike)
    : Option(expiry), _strike(strike) {
    if (expiry < 0 || strike < 0) {
        throw std::invalid_argument("The expiry and the strike can't be negative.");
    }
}

// Getter for strike
double EuropeanVanillaOption::getStrike() const {
    return _strike;
}
