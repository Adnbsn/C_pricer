#pragma once
#include "Option.h"

class AmericanOption : public Option {
public:
    // constructor
    AmericanOption(double expiry);

    // override to indicate it's an American option
    bool isAmericanOption() const override;

    // destructor
    virtual ~AmericanOption() = default;
};
