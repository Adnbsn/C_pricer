#include "AmericanPutOption.h"

AmericanPutOption::AmericanPutOption(double expiry, double strike)
    : AmericanOption(expiry), _strike(strike) {
}

double AmericanPutOption::payoff(double spot) const {
    return std::max(_strike - spot, 0.0);
}
