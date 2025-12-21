#include "CRRPricer.h"
#include <cmath>
#include <stdexcept>

/// <summary>
/// This is the first constructor for pricer
/// It is used when we already know the parameters (U, D, R)
/// </summary>
/// <param name="Option"></param>
/// <param name="Depth"></param>
/// <param name="asset_price"></param>
/// <param name="up"></param>
/// <param name="down"></param>
/// <param name="interest_rate"></param>
CRRPricer::CRRPricer(Option* Option, int Depth, double asset_price, double up, double down, double interest_rate)
    : option(Option), depth(Depth), S0(asset_price), U(up), D(down), R(interest_rate)
{
    //CRR trees can't handle asian options. 
    if (option->isAsianOption())
    {
        throw std::invalid_argument("CRRPricer don't work for Asian options");
    }
    // We calculate the risk-neutral probability with the known parameters
    q = (R - D) / (U - D);

    b = false;

    BuildPriceTree();
}

/// <summary>
/// This is the second constructor for pricer that is overloaded.
/// For this one we use different parameters. We use volatility and risk free rate.
/// Here we calculate U, D and R thanks to this new parameters
/// </summary>
/// <param name="Option"></param> 
/// <param name="Depth"></param>
/// <param name="asset_price"></param>
/// <param name="r"></param>
/// <param name="volatility"></param>
CRRPricer::CRRPricer(Option* Option, int Depth, double asset_price, double r, double volatility)
    : option(Option), depth(Depth), S0(asset_price)
{
    //same crr can't handle asian option
    if (option->isAsianOption()) {
        throw std::invalid_argument("CRRPricer don't work for Asian options");
    }

    double T = option->getExpiry();   // this is the time/maturity of the option
    double h = T / Depth;             // this is a time length for each steps.

    //now we calculate the parameters to approximate the black scholes model
    double k = r + 0.5 * volatility * volatility;
    U = std::exp(k * h + volatility * std::sqrt(h)) - 1.0;
    D = std::exp(k * h - volatility * std::sqrt(h)) - 1.0;
    R = std::exp(r * h) - 1.0;

    // We calculate the risk-neutral probability with the known parameters
    q = (R - D) / (U - D);
    b = false;

    BuildPriceTree();
}

/// <summary>
/// This is a tree that will follow the different changes in price that can happen to the stock.
/// Everywhere the stock can go between now and the end.
/// </summary>
void CRRPricer::BuildPriceTree() {
    price_tree.setDepth(depth);
    for (int n = 0; n <= depth; n++) {
        for (int j = 0; j <= n; j++) {
            double price = S0 * std::pow(1 + U, j) * std::pow(1 + D, n - j);
            price_tree.setNode(n, j, price);
        }
    }
}

/// <summary>
/// 
/// </summary>
void CRRPricer::compute() {
    option_tree.setDepth(depth);
    exercise_tree.setDepth(depth);   //we need the 2nd tree to know where we exercised early

    // We start by going to the end of the tree
    // The value of the leaf nodes are the payoff at expiry
    for (int i = 0; i <= depth; ++i) {

        // we get the stock price at the final node
        double spot = price_tree.getNode(depth, i);

        //we use the payoff function
        double payoff_val = option->payoff(spot);

        option_tree.setNode(depth, i, payoff_val);

        // If we make money, which mean payoff > 0, we exercise.
        exercise_tree.setNode(depth, i, payoff_val > 0.0);
    }

    // Now we do a backward induction
    // Since we have values at the leaf nodes, we use them to move back up in the tree
    // so from depth - 1 to the initial spot 0
    for (int n = depth - 1; n >= 0; --n) {
        for (int i = 0; i <= n; ++i) {
            // So here we take the values of the next time step (if we at the first iteration it would be the leaf)
            double upVal = option_tree.getNode(n + 1, i + 1);
            double downVal = option_tree.getNode(n + 1, i);

            //continuation computation, which is the expected gain if they do not exercise, under the risk-neutral measure
            double continuation = (q * upVal + (1.0 - q) * downVal) / (1.0 + R);

            //This is the spot price so the value if we exercise right now
            double spot = price_tree.getNode(n, i);
            double intrinsic = option->payoff(spot);

            double val;
            bool exercise = false;

            //american option are different because they can be used at any time unlike european one
            if (option->isAmericanOption()) {
                // So now if the option is American, we have to choose between
                // Keeping the option, if max is the continuation value
                // Or exercising it now, if max is the Intrinsic value
                if (intrinsic >= continuation) {
                    val = intrinsic;
                    exercise = true;
                }
                else {
                    val = continuation;
                    exercise = false;   //we better wait
                }
            }
            else {
                // For Europeans we are forced to wait anyway 
                // So we ignore the intrinsic value and care about continuation
                val = continuation;
                exercise = false;
            }

            option_tree.setNode(n, i, val);
            // Save info on if we decided to exercise or not
            exercise_tree.setNode(n, i, exercise);
        }
    }

    b = true;
}

/// <summary>
/// Just a getter to get the value of a node of the tree
/// </summary>
/// <param name="n"></param>
/// <param name="i"></param>
/// <returns></returns>
double CRRPricer::get(int n, int i) {
    if (n < 0 || n > depth) {
        throw std::out_of_range("the n value is higher than depth or negative");
    }
    if (i < 0 || i > n) {
        throw std::out_of_range("The i value is higher than the current row n or negative");
    }
    return option_tree.getNode(n, i);
}

/// <summary>
/// Just a getter to get the information on if we exercised or not the option
/// </summary>
/// <param name="n"></param>
/// <param name="i"></param>
/// <returns></returns>
bool CRRPricer::getExercise(int n, int i) {
    if (n < 0 || n > depth) {
        throw std::out_of_range("the n value is higher than depth or negative");
    }
    if (i < 0 || i > n) {
        throw std::out_of_range("The i value is higher than the current row n or negative");
    }
    return exercise_tree.getNode(n, i);
}

/// <summary>
/// We create the operator ()
/// It is used to return the current value of the option
/// </summary>
/// <param name="closed_form"></param>
/// <returns></returns>
double CRRPricer::operator()(bool closed_form) {
    // Tree Calculation for closed_form = false
    // This uses backward induction. It is slower but works for both American and European
    if (!closed_form) {
        if (!b) compute(); // Make sure we made the calculation
        return option_tree.getNode(0, 0);
    }
    //the eazy calculation for only european :
    //We just sum the different leaf values multiply by there probabilities (so basically just the expectation formula)
    double sum = 0.0;
    for (int i = 0; i <= depth; ++i) {
        double payoff = option->payoff(S0 * std::pow(1.0 + U, i) * std::pow(1.0 + D, depth - i));
        // This is the formula for the easier method
        sum += (std::tgamma(depth + 1) / (std::tgamma(i + 1) * std::tgamma(depth - i + 1))) * std::pow(q, i) * std::pow(1.0 - q, depth - i) * payoff;
    }
    //and here we do the actualisation (discount the price back for today value)
    return sum / std::pow(1.0 + R, depth);
}

