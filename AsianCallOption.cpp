#include "AsianCallOption.h"

// Constructor
AsianCallOption::AsianCallOption(const std::vector<double>& path, double strike)
    : AsianOption(path), _strike(strike)
{
    if (strike < 0.0)
    {
        throw std::invalid_argument("AsianCallOption: strike must be >= 0");
    }
}

// Override payoff
double AsianCallOption::payoff(double avgSpot) const
{
    if (avgSpot > _strike)
    {
        return avgSpot - _strike;
    }
    return 0.0;
}

// getter strike
double AsianCallOption::getStrike() const
{
    return _strike;

}

