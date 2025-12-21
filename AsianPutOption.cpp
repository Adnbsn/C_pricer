#include "AsianPutOption.h"

AsianPutOption::AsianPutOption(const std::vector<double>& path, double strike)
    : AsianOption(path), _strike(strike)
{
    if (strike < 0.0)
        throw std::invalid_argument("AsianPutOption: strike must be >= 0");
}

double AsianPutOption::payoff(double avgSpot) const
{
    if (_strike > avgSpot)
    {
        return _strike - avgSpot;
    }
    return 0.0;
}

double AsianPutOption::getStrike() const
{
    return _strike;

}
