#include "AsianOption.h"

AsianOption::AsianOption(const std::vector<double>& path)
    : Option(path.empty() ? 0.0 : path.back()), path(path)
{
    //We check if the list is empty
    if (path.empty()) {
        throw std::invalid_argument("The time cannot be empty");
    }

    //we check if the first date is non negative
    if (path.front() < 0.0) {
        throw std::invalid_argument("First time has to be >=0");
    }

    //we make sure that the times are increasing
    for (size_t i = 1; i < path.size(); ++i) {
        if (path[i] <= path[i - 1]) {
            throw std::invalid_argument("Time have to be increasing");
        }
    }
}




const std::vector<double>& AsianOption::getTimeSteps() const
{
    return path;
}

/// <summary>
/// calculate the average price of the path. Because it is what is used to then compare with the strike
/// It is the difference of the asian options
/// </summary>
/// <param name="spotPath"></param>
/// <returns></returns>
double AsianOption::payoffPath(const std::vector<double>& spotPath) const
{
    //We must have one price per date
    if (spotPath.size() != path.size())
        throw std::invalid_argument("Problem in the path size");

    double sum = 0.0;
    for (size_t i = 0; i < spotPath.size(); ++i)
    {
        sum = sum + spotPath[i];
    }

    double avg = sum / spotPath.size();
    return payoff(avg);      // This calls AsianCallOption/AsianPutOption payoff(double avg)
}

bool AsianOption::isAsianOption() const
{
    return true;
}