#include "Option.h"
#include <stdexcept>
#include <vector>

// Constructor
Option::Option(double expiry) : _expiry(expiry) {}

// Getter for expiry
double Option::getExpiry() const {
    return _expiry;
}

// Virtual destructor
Option::~Option() {}

double Option::payoffPath(const std::vector<double>& path) const
{
    if (path.empty())
    {
        throw std::invalid_argument("Path cannot be empty");
    }
    return payoff(path.back());
}

//Bool AsianOption
bool Option::isAsianOption() const
{
    return false;
}

//bool americanoption
bool Option::isAmericanOption() const {
    return false;
}