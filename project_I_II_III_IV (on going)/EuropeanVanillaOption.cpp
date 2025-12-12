#include "EuropeanVanillaOption.h"

// Constructor
EuropeanVanillaOption::EuropeanVanillaOption(double expiry, double strike)
    : Option(expiry), _strike(strike) {
    if (expiry < 0 || strike < 0) {
        throw std::invalid_argument("Expiry and strike must be non-negative.");
    }
}

// Getter for strike
double EuropeanVanillaOption::getStrike() const {
    return _strike;
}
