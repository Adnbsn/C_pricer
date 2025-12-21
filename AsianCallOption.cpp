#include "AsianCallOption.h"

AsianCallOption::AsianCallOption(const std::vector<double>& path, double strike)
    : AsianOption(path), _strike(strike)
{
    if (strike < 0.0)
        throw std::invalid_argument("For Asian option strike have to be >= 0");
}

/// <summary>
/// Unlike american and european options the asian option look at an average spot
/// </summary>
/// <param name="avgSpot"></param>
/// <returns></returns>
double AsianCallOption::payoff(double avgSpot) const
{   // If the average of the prices while the option was lasting is higher than the strike then we get 
    if (avgSpot > _strike)
    {
        return avgSpot - _strike;
    }
    //else we get nothing
    else {
        return 0.0;
    }
}

double AsianCallOption::getStrike() const
{
    return _strike;

}