#include "AmericanCallOption.h"

AmericanCallOption::AmericanCallOption(double expiry, double strike)
    : AmericanOption(expiry), _strike(strike) {
}

double AmericanCallOption::payoff(double spot) const {
    return std::max(spot - _strike, 0.0);
}
