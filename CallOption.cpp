#include "CallOption.h"

// Constructor
CallOption::CallOption(double expiry, double strike)
    : EuropeanVanillaOption(expiry, strike) {
}

// Payoff implementation
double CallOption::payoff(double spot) const {
    double K = getStrike();
    //if current price sup than the strike then we exerce the option and get spot - strike
    if (spot >= K) {
        return spot - K;
    }
    //else we do nothing
    else {
        return 0.0;
    }
}

// Option type implementation
CallOption::optionType CallOption::getOptionType() const {
    return optionType::call;
}
