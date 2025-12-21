#include "AmericanCallOption.h"

AmericanCallOption::AmericanCallOption(double expiry, double strike)    : AmericanOption(expiry), _strike(strike) {}

double AmericanCallOption::payoff(double spot) const {
    //if current price sup than the strike then we exerce the option and get spot - strike
    if (spot > _strike) {
        return spot-_strike;
    }
    //else we do nothing
    else {
        return 0.0;
    }
}
