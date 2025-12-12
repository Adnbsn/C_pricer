#include "BlackScholesMCPricer.h"
#include "Option.h"
#include <vector>
#include "AsianOption.h"
#include "MT.h"
#include <cmath>
#include <stdexcept>

//Constructor
BlackScholesMCPricer::BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility) :option(option), initial_price(initial_price), interest_rate(interest_rate), volatility(volatility)
{
    nbPaths = 0;
    sum_payoffs = 0;
    sum_payoffs_squared = 0;
    nb_paths_generated = 0;
}

// Getter for number of paths
int BlackScholesMCPricer::getNbPaths() const
{
    return nbPaths;
}

//generate function :
void BlackScholesMCPricer::generate(int nb_paths)
{
    double T = option->getExpiry();
    double discount_factor = std::exp(-interest_rate * T); //it's exp(-rT) in the H0 formula

    for (int i = 0; i < nb_paths; ++i) //we have to generate a payoff and prices for each path
    {
        double payoff = 0.0;
        // For European options (m = 1): HT = h(ST)
        if (!option->isAsianOption())
        {
            // Generate Z follows N(0,1)
            double Z = MT::rand_norm();
            // ST = S0 * exp((r - sigma²/2)T + sigma*sqrt(T) * Z)
            double ST = initial_price * std::exp((interest_rate - 0.5 * volatility * volatility) * T + volatility * std::sqrt(T) * Z);
            payoff = option->payoff(ST);
        }
        // For Asian options (m > 1): HT = h(St1, ..., Stm)
        else
        {
            AsianOption* asian_option = dynamic_cast<AsianOption*>(option);
            std::vector<double> time_steps = asian_option->getTimeSteps();
            std::vector<double> price_path;  // (St1, ..., Stm)
            double S_prev = initial_price;  // S0 here in the first iteration
            double t_prev = 0.0;

            for (int k = 0; k < time_steps.size(); k++)
            {
                // Generate Zk follows N(0,1)
                double Z_k = MT::rand_norm();
                // dt = tk - t_{k-1}
                double dt = time_steps[k] - t_prev;
                // S(tk) = S(t_{k-1}) * exp((r - sigma²/2)(tk - t_{k-1}) + sigma*sqrt((tk - t_{k-1}) * Zk))
                double S_k = S_prev * std::exp((interest_rate - 0.5 * volatility * volatility) * dt + volatility * std::sqrt(dt) * Z_k);
                price_path.push_back(S_k); //we add the new price at the end of the price paths
                S_prev = S_k; //we update the values of the previous price and previous time
                t_prev = time_steps[k];
            }
            // HT = h(St1, ..., Stm)
            payoff = option->payoffPath(price_path);
        }
        // Monte Carlo: H0 = e^(-rT) * (1/N) * sum h(Si_t1, ..., Si_tm)
        // We accumulate: sum_payoffs = sum e^(-rT) * h(...)
        double discounted_payoff = payoff * discount_factor;
        // Incremental update for mean and variance
        sum_payoffs += discounted_payoff;
        sum_payoffs_squared += discounted_payoff * discounted_payoff;
        nb_paths_generated++;
        nbPaths++;
    }
}

//operator ()
double BlackScholesMCPricer::operator()() const
{
    if (nb_paths_generated == 0)
    {
        throw std::runtime_error("No paths generated yet. Call generate() first.");
    }
    // H0 = (1/N) * sum discounted_payoffs
    return sum_payoffs / nb_paths_generated;
}

//
std::vector<double> BlackScholesMCPricer::confidenceInterval() const
{
    if (nb_paths_generated == 0)
    {
        throw std::runtime_error("No paths generated yet. Call generate() first.");
    }
    // Mean estimate
    double mean = sum_payoffs / nb_paths_generated;
    // Variance estimate: Var = E[X²] - E[X]²
    double variance = (sum_payoffs_squared / nb_paths_generated) - (mean * mean);
    // Standard error: SE = sqrt(Var / N)
    double std_error = std::sqrt(variance / nb_paths_generated);

    std::vector<double> ci;
    ci.push_back(mean - 1.96 * std_error);  // For Z follows N(0,1) P(-1.96 <= Z <= 1.96) = 0.95 with Z=(X-mean)/std
    ci.push_back(mean + 1.96 * std_error);
    return ci;
}