#pragma once
#include "EuropeanVanillaOption.h"

class CallOption : public EuropeanVanillaOption {
public:
    CallOption(double expiry, double strike);

    // Payoff function
    double payoff(double spot) const override;

    // Option type
    optionType getOptionType() const override;
};
