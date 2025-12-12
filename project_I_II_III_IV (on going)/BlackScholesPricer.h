#pragma once
#include <iostream>
#include <cmath>
#include <stdexcept>
#include "EuropeanVanillaOption.h"
#include "EuropeanDigitalOption.h"

class BlackScholesPricer {
public:
    // Constructor for Vanilla options
    BlackScholesPricer(EuropeanVanillaOption* opt, double asset_price, double interest_rate, double volatility);

    // Overloaded constructor for Digital options
    BlackScholesPricer(EuropeanDigitalOption* opt, double asset_price, double interest_rate, double volatility);

    // Operator() returns Black-Scholes price
    double operator()();

    // Delta
    double delta();

private:
    EuropeanVanillaOption* vanillaOption; // Pointer for Vanilla
    EuropeanDigitalOption* digitalOption; // Pointer for Digital
    double S;     // Current asset price
    double r;     // Risk-free interest rate
    double sigma; // Volatility

    constexpr static double PI = 3.14159265358979323846;

    // Standard normal cumulative distribution function (CDF)
    double N(double x);

    // Standard normal probability density function (PDF)
    double n(double x);
};
