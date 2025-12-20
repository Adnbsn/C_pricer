#include "BlackScholesPricer.h"
//Constructors
BlackScholesPricer::BlackScholesPricer(EuropeanVanillaOption* opt, double asset_price, double interest_rate, double volatility)
    : vanillaOption(opt), digitalOption(nullptr), S(asset_price), r(interest_rate), sigma(volatility) {
}

BlackScholesPricer::BlackScholesPricer(EuropeanDigitalOption* opt, double asset_price, double interest_rate, double volatility)
    : vanillaOption(nullptr), digitalOption(opt), S(asset_price), r(interest_rate), sigma(volatility) {
}

//CDF
double BlackScholesPricer::N(double x) {
    return 0.5 * std::erfc(-x / std::sqrt(2));
}
//PDF
double BlackScholesPricer::n(double x) {
    return (1.0 / std::sqrt(2.0 * PI)) * std::exp(-0.5 * x * x);
}

// Operator () 
double BlackScholesPricer::operator()() {
    //we check if we are in the case of vanilla or digital option
    if (vanillaOption) {
        double K = vanillaOption->getStrike();
        double T = vanillaOption->getExpiry();
        double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
        double d2 = d1 - sigma * std::sqrt(T);

        //formulas for it we are in a call or put case
        //Call payoff (at expiry): max ⁡ ( S_t − K , 0 )
        //Put payoff (at expiry): max ⁡ ( K − S_t , 0 ) 

        if (vanillaOption->getOptionType() == EuropeanVanillaOption::optionType::call) {
            return S * N(d1) - K * std::exp(-r * T) * N(d2);
        }
        else {
            return K * std::exp(-r * T) * N(-d2) - S * N(-d1);
        }
    }
    else if (digitalOption) {
        double K = digitalOption->getStrike();
        double T = digitalOption->getExpiry();
        double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
        double d2 = d1 - sigma * std::sqrt(T);

        if (digitalOption->getOptionType() == EuropeanDigitalOption::optionType::call) {
            return std::exp(-r * T) * N(d2);
        }
        else {
            return std::exp(-r * T) * N(-d2);
        }
    }

    throw std::runtime_error("BlackScholesPricer not initialized with an option.");
}

double BlackScholesPricer::delta() {
    if (vanillaOption) {
        double K = vanillaOption->getStrike();
        double T = vanillaOption->getExpiry();
        double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));

        if (vanillaOption->getOptionType() == EuropeanVanillaOption::optionType::call) {
            return N(d1);
        }
        else {
            return N(d1) - 1.0;
        }
    }
    else if (digitalOption) {
        double K = digitalOption->getStrike();
        double T = digitalOption->getExpiry();
        double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
        double d2 = d1 - sigma * std::sqrt(T);

        if (digitalOption->getOptionType() == EuropeanDigitalOption::optionType::call) {
            return std::exp(-r * T) * n(d2) / (S * sigma * std::sqrt(T));
        }
        else {
            return -std::exp(-r * T) * n(d2) / (S * sigma * std::sqrt(T));
        }
    }

    throw std::runtime_error("BlackScholesPricer not initialized with an option.");
}
