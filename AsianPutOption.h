#pragma once
#include "AsianOption.h"
#include <stdexcept>
#include <vector>

class AsianPutOption : public AsianOption
{
private:
    double _strike;

public:

    //constructor
    AsianPutOption(const std::vector<double>& path, double strike);

    // override payoff
    double payoff(double avgSpot) const override;

    // getter strike
    double getStrike() const;
};

