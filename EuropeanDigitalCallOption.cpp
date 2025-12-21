#include "EuropeanDigitalCallOption.h"

/*
  EuropeanDigitalCallOption represents a European cash or nothing digital CALL option
  Reminder on its characteristics
  It pays a fixed amount (1 unit of cash)
  Payment occurs at maturity only
  Payoff depends mainly on the terminal spot price S_T
  The parameters are time to maturity (T) and strike price (K)
*/


EuropeanDigitalCallOption::EuropeanDigitalCallOption(double expiry, double strike)
    : EuropeanDigitalOption(expiry, strike) {
}

// payoff for a put digital option
// it is a fix payoff so only need to check if condition for the payoff is true or not

double EuropeanDigitalCallOption::payoff(double spot) const {
    //spot sup than the strike so we get money
    if (spot >= getStrike()) {
        return 1.0;
    }
    //else we don't get anything
    else {
        return 0.0;
    }
}

/*
OPTION Type identification returns the option type (call or put)
Required by pricers to select the appropriate pricing and Greek formulas
*/

EuropeanDigitalOption::optionType EuropeanDigitalCallOption::getOptionType() const {
    return optionType::call;
}
