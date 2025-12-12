#include "EuropeanDigitalPutOption.h"

EuropeanDigitalPutOption::EuropeanDigitalPutOption(double expiry, double strike)
    : EuropeanDigitalOption(expiry, strike) {
}

double EuropeanDigitalPutOption::payoff(double spot) const {
    if (spot <= getStrike()) {
        return 1.0;
    }
    else {
        return 0.0;
    }
}

EuropeanDigitalOption::optionType EuropeanDigitalPutOption::getOptionType() const {
    return optionType::put;
}
