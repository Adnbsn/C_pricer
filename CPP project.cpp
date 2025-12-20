#include <iostream>
#include <cmath>
#include <stdexcept>

class Option {
private:
    double _expiry;

public: //constructor
    Option(double expiry) : _expiry(expiry) {}
    double getExpiry() {
        return _expiry;
    }

    //virtual method
    virtual double payoff(double spot) const = 0;
    //virtual destructor
    virtual ~Option() {}
};

class EuropeanVanillaOption : public Option {
private:
    double _strike;

public:
    EuropeanVanillaOption(double expiry, double strike)
        : Option(expiry), _strike(strike) {
        if (expiry < 0 || strike < 0) {
            throw std::invalid_argument("Expiry and strike must be non-negative.");
        }
    }

    double getStrike() const { 
        return _strike; }

public:
    enum class optionType { call, put };
    virtual optionType getOptionType() const = 0;

    // Grant access to BlackScholesPricer
    friend class BlackScholesPricer;
};

class callOption : public EuropeanVanillaOption {
public:
    callOption(double expiry, double strike) : EuropeanVanillaOption(expiry, strike) {}

    //payoff
    double payoff(double spot) const override {
        double K = getStrike();
        return (spot >= K) ? (spot - K) : 0.0;
    }

    //tyope d'options
    optionType getOptionType() const override {
        return optionType::call;
    }
};

class putOption : public EuropeanVanillaOption {
public:
    putOption(double expiry, double strike) : EuropeanVanillaOption(expiry, strike) {}

    double payoff(double spot) const override {
        double K = getStrike();
        return (spot <= K) ? (K - spot) : 0.0;
    }

    optionType getOptionType() const override {
        return optionType::put;
    }
};


//implementation de BS
class BlackScholesPricer {
public:
    BlackScholesPricer(EuropeanVanillaOption* option, double asset_price,
        double interest_rate, double volatility)
        : option(option), S(asset_price), r(interest_rate), sigma(volatility) {
    }

    // Operator() returns Black-Scholes price
    double operator()();

    // Delta 
    double delta();

private:
    EuropeanVanillaOption* option;
    double S;     // Current asset price
    double r;     // Risk-free interest rate
    double sigma; // Vol

    // Standard normal cumulative distribution function
    double N(double x) {
        return 0.5 * std::erfc(-x / std::sqrt(2));
    }
};


//utilisation de BS
double BlackScholesPricer::operator()() {
    double K = option->getStrike();
    double T = option->getExpiry();
    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);

    if (option->getOptionType() == EuropeanVanillaOption::optionType::call) {
        return S * N(d1) - K * std::exp(-r * T) * N(d2);
    }
    else {             //ici on fait le put
        return K * std::exp(-r * T) * N(-d2) - S * N(-d1);  
    }
}

//on retourne le delta
double BlackScholesPricer::delta() {
    double K = option->getStrike();
    double T = option->getExpiry();
    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));

    if (option->getOptionType() == EuropeanVanillaOption::optionType::call) {
        return N(d1);
    }
    else {    //put 
        return N(d1) - 1.0;
    }
}



// --- main ---
#include <iostream>

int main() {
    try {
        double S = 100.0;     // Spot price
        double K = 100.0;     // Strike
        double r = 0.05;      // Risk-free rate
        double sigma = 0.2;   // Vol
        double T = 1.0;       // Maturity (1 year)

        callOption call(T, K);
        putOption put(T, K);

        BlackScholesPricer pricerCall(&call, S, r, sigma);
        BlackScholesPricer pricerPut(&put, S, r, sigma);

        std::cout << "Call price = " << pricerCall() << std::endl;
        std::cout << "Put price  = " << pricerPut() << std::endl;

        std::cout << "Call delta = " << pricerCall.delta() << std::endl;
        std::cout << "Put delta  = " << pricerPut.delta() << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
