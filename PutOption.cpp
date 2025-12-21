#include "PutOption.h"

// Constructor
PutOption::PutOption(double expiry, double strike)
    : EuropeanVanillaOption(expiry, strike) {
}

// Payoff for a put
double PutOption::payoff(double spot) const {
    double K = getStrike();
    //for a put we want the strike greater than the spot since it is to sell and not buy
    if (spot <= K) {
        return K - spot;
    }
    //if strike not greater then we do nothing
    else {
        return 0.0;
    }
}

// getter for option type
PutOption::optionType PutOption::getOptionType() const {
    return optionType::put;
}
