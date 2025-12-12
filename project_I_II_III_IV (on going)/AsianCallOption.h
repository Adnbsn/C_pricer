#pragma once
#include "AsianOption.h"
#include <stdexcept>
#include <vector>

class AsianCallOption : public AsianOption
{
private:
    double _strike;

public:
    // FIX: constructor uses const reference
    AsianCallOption(const std::vector<double>& path, double strike);

    // FIX: payoff must use avgSpot, not "strike"
    double payoff(double avgSpot) const override;

    double getStrike() const;
};
