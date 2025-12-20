#pragma once
#include "EuropeanDigitalOption.h"

class EuropeanDigitalCallOption : public EuropeanDigitalOption
{
public:
    // Constructor
    EuropeanDigitalCallOption(double expiry, double strike);

    // New methods for digital call option
    double payoff(double spot) const override;
    optionType getOptionType() const override;
};