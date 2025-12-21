#include "AmericanPutOption.h"

AmericanPutOption::AmericanPutOption(double expiry, double strike)  : AmericanOption(expiry), _strike(strike) {}

double AmericanPutOption::payoff(double spot) const {
    //for a put we want the strike greater than the spot since it is to sell and not buy
    if (spot < _strike) {
        return _strike - spot;
    }
    //if strike not greater then we do nothing
    else {
        return 0.0;
    }
}
