#pragma once
#include "EuropeanVanillaOption.h"

class PutOption : public EuropeanVanillaOption {
public:
    PutOption(double expiry, double strike);

    // Payoff function
    double payoff(double spot) const override;

    // Option type
    optionType getOptionType() const override;
};
