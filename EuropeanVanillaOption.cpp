#include "EuropeanVanillaOption.h"

/*
EuropeanVanillaOption represents a standard European option contract
Reminder of its characteristics:
payoff is evaluated at maturity T only
linear payoff (call or put) and fixed exercise price K
This class stores the strike price and inherits the expiry from the Option class.
*/

// Constructor
EuropeanVanillaOption::EuropeanVanillaOption(double expiry, double strike)
    : Option(expiry), _strike(strike) {

    /* Contract validation: expiry must be non-negative and strike must be non-negative
    Negative values do not correspond to a valid financial contract
    */
    if (expiry < 0 || strike < 0) {
        throw std::invalid_argument("The expiry and the strike can't be negative.");
    }
}

// Getter for strike: returns the strike price K of the vanilla option used by the pricer

double EuropeanVanillaOption::getStrike() const {
    return _strike;
}
