#pragma once
#include "Option.h"
#include <stdexcept>

class EuropeanVanillaOption : public Option {
private:
    double _strike;

public:
    // Constructor
    EuropeanVanillaOption(double expiry, double strike);

    // Getter for strike
    double getStrike() const;

    // Enum for option type
    enum class optionType { call, put };

    // Pure virtual method to get option type
    virtual optionType getOptionType() const = 0;

    // Grant access to BlackScholesPricer
    friend class BlackScholesPricer;
};
