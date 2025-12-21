#include "EuropeanDigitalPutOption.h"

/*
EuropeanDigitalPutOption represents a European cash or nothing digital PUT option.
Reminder on its characteristics
It pays a fixed amount (1 unit of cash)
Payoff is evaluated at maturity only
It depends mainly on the terminal spot price S_T
*/

EuropeanDigitalPutOption::EuropeanDigitalPutOption(double expiry, double strike)
    : EuropeanDigitalOption(expiry, strike) {

}

// payoff for a put digital option
// it is a fix payoff so only need to check if condition for the payoff is true or not

double EuropeanDigitalPutOption::payoff(double spot) const {
    // To check if the option finishes in the money
    if (spot <= getStrike()) {
        return 1.0;
    }
    else {
        return 0.0;
    }
}

// This returns the option type (put) and allows pricers to apply the correct pricing and Greek formulas

EuropeanDigitalOption::optionType EuropeanDigitalPutOption::getOptionType() const {
    return optionType::put;
}
