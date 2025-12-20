#include "PutOption.h"

// Constructor
PutOption::PutOption(double expiry, double strike)
    : EuropeanVanillaOption(expiry, strike) {
}

// Payoff for a put
double PutOption::payoff(double spot) const {
    double K = getStrike();
    if (spot <= K) {
        return K - spot;
    }
    else {
        return 0.0;
    }
}

// getter for option type
PutOption::optionType PutOption::getOptionType() const {
    return optionType::put;
}
