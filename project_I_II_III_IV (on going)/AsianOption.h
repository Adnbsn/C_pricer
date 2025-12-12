#pragma once
#include "Option.h"
#include <stdexcept>
#include <vector>

class AsianOption : public Option
{
protected:
    // Keep your old name "path" for minimal change
    std::vector<double> path;

public:
    // FIX: constructor must take const reference 
    explicit AsianOption(const std::vector<double>& path);

    // FIX: MUST return const reference (not a copy!)
    const std::vector<double>& getTimeSteps() const;

    // FIX: signature matches Option virtual method
    double payoffPath(const std::vector<double>& spotPath) const override;

    // FIX: matches MCPricer expectations
    bool isAsianOption() const override;
};
