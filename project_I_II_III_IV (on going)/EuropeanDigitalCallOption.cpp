#include "EuropeanDigitalCallOption.h"

EuropeanDigitalCallOption::EuropeanDigitalCallOption(double expiry, double strike)
    : EuropeanDigitalOption(expiry, strike) {
}

double EuropeanDigitalCallOption::payoff(double spot) const {
    if (spot >= getStrike()) {
        return 1.0;
    }
    else {
        return 0.0;
    }
}

EuropeanDigitalOption::optionType EuropeanDigitalCallOption::getOptionType() const {
    return optionType::call;
}
