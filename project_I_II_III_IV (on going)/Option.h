#pragma once
#include<vector>

class Option {
private:
    double _expiry;

public:
    // Constructor
    Option(double expiry);

    // Getter for expiry
    double getExpiry() const;

    // Pure virtual payoff method
    virtual double payoff(double spot) const = 0;

    // Virtual destructor
    virtual ~Option();

    // Path-dependent payoff method
    virtual double  payoffPath(const std::vector<double>& path) const;

    //Bool method AsianOption
    virtual bool isAsianOption() const;

    //bool method AmericanOptiion
    virtual bool isAmericanOption() const;
};
