#pragma once
#include "Option.h"
#include <stdexcept>
#include <vector>

class AsianOption : public Option
{
protected:
    std::vector<double> path;

public:

    explicit AsianOption(const std::vector<double>& path);


    const std::vector<double>& getTimeSteps() const;

 
    double payoffPath(const std::vector<double>& spotPath) const override;


    bool isAsianOption() const override;
};

