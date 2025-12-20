#include "CallOption.h"

// Constructor
CallOption::CallOption(double expiry, double strike)
    : EuropeanVanillaOption(expiry, strike) {
}

// Payoff implementation
double CallOption::payoff(double spot) const {
    double K = getStrike();
    if (spot >= K) {
        return spot - K;
    }
    else {
        return 0.0;
    }
}

// Option type implementation
CallOption::optionType CallOption::getOptionType() const {
    return optionType::call;
}
