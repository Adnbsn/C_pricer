#include "AsianPutOption.h"

// constructor
AsianPutOption::AsianPutOption(const std::vector<double>& path, double strike)
    : AsianOption(path), _strike(strike)
{
    if (strike < 0.0)
    {
        throw std::invalid_argument("AsianPutOption: strike must be >= 0");
    }
}

/// <summary>
/// Unlike american and european options the asian option look at an average spot
/// </summary>
/// <param name="avgSpot"></param>
/// <returns></returns>
double AsianPutOption::payoff(double avgSpot) const
{   // If the average of the prices while the option was lasting is lower than the strike then we get 
    if (_strike > avgSpot)
    {
        return _strike - avgSpot;
    }
    //else we get nothing
    else {
        return 0.0;
    }
}

// getter for strike
double AsianPutOption::getStrike() const
{
    return _strike;

}
