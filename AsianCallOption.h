#pragma once
#include "AsianOption.h"
#include <stdexcept>
#include <vector>

class AsianCallOption : public AsianOption
{
private:
    double _strike;

public:
    // Constructor
    AsianCallOption(const std::vector<double>& path, double strike);

    //override payoff
    double payoff(double avgSpot) const override;

    // getter for strike
    double getStrike() const;
};


