#include "EuropeanDigitalOption.h"

/*
EuropeanDigitalOption is an abstract representation of a European digital (binary) option.
Main features are European (payoff evaluated at maturity T only) and Digital (payoff discontinuous due to binary outcome)
This class stores expiry (from Option) and strike price K
*/


EuropeanDigitalOption::EuropeanDigitalOption(double expiry, double Strike)
    : Option(expiry), strike(Strike)
{

    /*
    Input validation: expiry must be non-negative and strike must be non-negative
    To prevent meaningless financial contracts like negative maturity or strike
    */
    if (expiry < 0 || Strike < 0) {
        throw std::invalid_argument("Expiry and strike must be non negative");
    }
}

// Strike getter:  returns the strike price K of the digital option

double EuropeanDigitalOption::getStrike() const {
    return strike;
}
