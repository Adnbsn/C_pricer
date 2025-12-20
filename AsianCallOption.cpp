#include "AsianCallOption.h"

AsianCallOption::AsianCallOption(const std::vector<double>& path, double strike)
    : AsianOption(path), _strike(strike)
{
    if (strike < 0.0)
        throw std::invalid_argument("AsianCallOption: strike must be >= 0");
}

double AsianCallOption::payoff(double avgSpot) const
{
    return (avgSpot > _strike) ? (avgSpot - _strike) : 0.0;
}

double AsianCallOption::getStrike() const
{
    return _strike;
}