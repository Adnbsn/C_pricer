#pragma once
#include <stdexcept>
#include "EuropeanVanillaOption.h" 

class EuropeanDigitalOption : public Option
{
private:
    double strike;

public:
    // Constructeur
    EuropeanDigitalOption(double expiry, double Strike);

    // Getter
    double getStrike() const;

    // option type inherited from europeaVanillaOption
    using optionType = EuropeanVanillaOption::optionType;
    virtual optionType getOptionType() const = 0;
};
