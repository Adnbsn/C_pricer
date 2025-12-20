#include "AsianOption.h"

AsianOption::AsianOption(const std::vector<double>& path)
    : Option(path.empty() ? 0.0 : path.back()), path(path)
{
    if (path.empty())
        throw std::invalid_argument("AsianOption: time grid cannot be empty");

    if (path.front() < 0.0)
        throw std::invalid_argument("AsianOption: first time must be >= 0");

    for (size_t i = 1; i < path.size(); ++i)
        if (path[i] <= path[i - 1])
            throw std::invalid_argument("AsianOption: times must be increasing");
}

const std::vector<double>& AsianOption::getTimeSteps() const
{
    return path;
}

double AsianOption::payoffPath(const std::vector<double>& spotPath) const
{
    if (spotPath.size() != path.size())
        throw std::invalid_argument("AsianOption: spot path length mismatch");

    double sum = 0.0;
    for (double s : spotPath)
        sum += s;

    double avg = sum / spotPath.size();
    return payoff(avg);      // This calls AsianCallOption/AsianPutOption payoff(double avg)
}

bool AsianOption::isAsianOption() const
{
    return true;
}