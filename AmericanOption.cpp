#include "AmericanOption.h"

AmericanOption::AmericanOption(double expiry)
    : Option(expiry)
{
}

// implémentation de la méthode virtuelle overridée
bool AmericanOption::isAmericanOption() const
{
    return true;
}
