#pragma once
#include "AmericanOption.h"
#include <algorithm>

class AmericanPutOption : public AmericanOption {
private:
    double _strike;

public:
    // Constructor
    AmericanPutOption(double expiry, double strike);

    // Payoff override
    double payoff(double spot) const override;

    virtual ~AmericanPutOption() = default;
};

