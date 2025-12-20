#include "EuropeanDigitalCallOption.h"

EuropeanDigitalCallOption::EuropeanDigitalCallOption(double expiry, double strike)
    : EuropeanDigitalOption(expiry, strike) {
}

//payoff for a put digital option
//it is a fix payoff so only need to check if condition
// for the payoff is true or not
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
