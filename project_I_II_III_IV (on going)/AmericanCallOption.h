#pragma once
#include "AmericanOption.h"
#include <algorithm>

class AmericanCallOption : public AmericanOption {
private:
    double _strike;

public:
    // Constructor
    AmericanCallOption(double expiry, double strike);

    // Payoff override
    double payoff(double spot) const override;

    virtual ~AmericanCallOption() = default;
};

