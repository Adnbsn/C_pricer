#include "BlackScholesPricer.h"

/*
The pricer can price:
a European vanilla option (call or put)
a European digital option (cash or nothing)
*/


// Constructor for European vanilla options
BlackScholesPricer::BlackScholesPricer(EuropeanVanillaOption* opt, double asset_price, double interest_rate, double volatility)
    : vanillaOption(opt), digitalOption(nullptr), S(asset_price), r(interest_rate), sigma(volatility) {
}

// Constructor for European digital options
BlackScholesPricer::BlackScholesPricer(EuropeanDigitalOption* opt, double asset_price, double interest_rate, double volatility)
    : vanillaOption(nullptr), digitalOption(opt), S(asset_price), r(interest_rate), sigma(volatility) {
}

//CDF of the normal law
double BlackScholesPricer::N(double x) {
    return 0.5 * std::erfc(-x / std::sqrt(2));
}
//PDF of the normal law
double BlackScholesPricer::n(double x) {
    return (1.0 / std::sqrt(2.0 * PI)) * std::exp(-0.5 * x * x);
}

/* Operator() returns the Black–Scholes price of the option.
It detects whether the pricer was initialized with a vanilla option or a digital option
and applies the corresponding closed form formula
*/

double BlackScholesPricer::operator()() {
    //we check if we are in the case of vanilla or digital option

    // VANILLA OPTION PRICING
    if (vanillaOption) {

        // Option parameters
        double K = vanillaOption->getStrike(); // strike price
        double T = vanillaOption->getExpiry(); // time to maturity

        // Black–Scholes d1 and d2 terms
        double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
        double d2 = d1 - sigma * std::sqrt(T);

        //formulas for it we are in a call or put case
        /* Payoffs at maturity :
        Call: max(S_T - K, 0)
        Put : max(K - S_T, 0)
        Black–Scholes closed - form prices :
        Call = S N(d1) - K e^{-rT} N(d2)
        Put = K e^{-rT} N(-d2) - S N(-d1)
        */

        if (vanillaOption->getOptionType() == EuropeanVanillaOption::optionType::call) {
            return S * N(d1) - K * std::exp(-r * T) * N(d2);
        }
        else {
            return K * std::exp(-r * T) * N(-d2) - S * N(-d1);
        }
    }

    // DIGITAL OPTION PRICING
    else if (digitalOption) {
        double K = digitalOption->getStrike();
        double T = digitalOption->getExpiry();
        double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
        double d2 = d1 - sigma * std::sqrt(T);

        /* Cash vs nothing digital option:
        Pays 1 unit of cash if in-the-money at maturity
        Discounted back to present value
        Prices will be:
        Call = e^{-rT} N(d2)
        Put = e^{-rT} N(-d2)
        */

        if (digitalOption->getOptionType() == EuropeanDigitalOption::optionType::call) {
            return std::exp(-r * T) * N(d2);
        }
        else {
            return std::exp(-r * T) * N(-d2);
        }
    }
    // Safety check for initialization
    throw std::runtime_error("BlackScholesPricer not initialized with an option.");
}


// Delta measures the sensitivity of the option price to changes in the underlying asset price S

double BlackScholesPricer::delta() {

    // VANILLA OPTION DELTA
    if (vanillaOption) {
        double K = vanillaOption->getStrike();
        double T = vanillaOption->getExpiry();
        double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));

        /* Vanilla deltas:
        Call: delta = N(d1)
        Put : delta = N(d1)-1
        */

        if (vanillaOption->getOptionType() == EuropeanVanillaOption::optionType::call) {
            return N(d1);
        }
        else {
            return N(d1) - 1.0;
        }
    }

    // DIGITAL OPTION DELTA
    else if (digitalOption) {
        double K = digitalOption->getStrike();
        double T = digitalOption->getExpiry();
        double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
        double d2 = d1 - sigma * std::sqrt(T);

        /* Digital deltas:
        delta = +/- e^{-rT} N(d2) / (S σ sqrt(T))
        */
        if (digitalOption->getOptionType() == EuropeanDigitalOption::optionType::call) {
            return std::exp(-r * T) * n(d2) / (S * sigma * std::sqrt(T));
        }
        else {
            return -std::exp(-r * T) * n(d2) / (S * sigma * std::sqrt(T));
        }
    }

    // Safety check for initialization
    throw std::runtime_error("BlackScholesPricer not initialized with an option.");
}
