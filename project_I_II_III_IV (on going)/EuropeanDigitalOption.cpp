#include "EuropeanDigitalOption.h"

EuropeanDigitalOption::EuropeanDigitalOption(double expiry, double Strike)
    : Option(expiry), strike(Strike)
{
    if (expiry < 0 || Strike < 0) {
        throw std::invalid_argument("Expiry and strike must be non-negative.");
    }
}

double EuropeanDigitalOption::getStrike() const {
    return strike;
}
