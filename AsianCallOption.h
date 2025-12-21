#pragma once
#include "AsianOption.h"
#include <stdexcept>
#include <vector>

class AsianCallOption : public AsianOption
{
private:
    double _strike;

public:
    
    AsianCallOption(const std::vector<double>& path, double strike);

    double payoff(double avgSpot) const override;

    double getStrike() const;
};

