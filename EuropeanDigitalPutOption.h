#pragma once
#include "EuropeanDigitalOption.h"

class EuropeanDigitalPutOption : public EuropeanDigitalOption
{
public:
    // Constructor
    EuropeanDigitalPutOption(double expiry, double strike);

    // new methods for digital put optoin
    double payoff(double spot) const override;
    optionType getOptionType() const override;
};
