#pragma once
#include "Option.h"
#include <stdexcept>
#include <vector>

class AsianOption : public Option
{
protected:
    std::vector<double> path;

public:

    // constructor
    explicit AsianOption(const std::vector<double>& path);

    // getter timesteps
    const std::vector<double>& getTimeSteps() const;

     // ovveride payoffpath
    double payoffPath(const std::vector<double>& spotPath) const override;

    // Override bool isAsianOption 
    bool isAsianOption() const override;
};


