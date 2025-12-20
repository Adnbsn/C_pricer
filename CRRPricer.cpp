#include "CRRPricer.h"
#include <cmath>
#include <stdexcept>

CRRPricer::CRRPricer(Option* Option, int Depth, double asset_price, double up, double down, double interest_rate)
    : option(Option), depth(Depth), S0(asset_price), U(up), D(down), R(interest_rate)
{
    if (option->isAsianOption()) 
    {
        throw std::invalid_argument("CRRPricer cannot price Asian options");
    }
    q = (R - D) / (U - D);

    b = false;

    BuildPriceTree();
}

// AJOUT : constructeur Black–Scholes (Section 6)
CRRPricer::CRRPricer(Option* Option, int Depth, double asset_price, double r, double volatility)
    : option(Option), depth(Depth), S0(asset_price)
{
    if (option->isAsianOption()) {
        throw std::invalid_argument("CRRPricer cannot price Asian options");
    }

    double T = option->getExpiry();   // get the time of the option
    double h = T / Depth;             // pas de temps

    double drift = r + 0.5 * volatility * volatility;
    U = std::exp(drift * h + volatility * std::sqrt(h)) - 1.0;
    D = std::exp(drift * h - volatility * std::sqrt(h)) - 1.0;
    R = std::exp(r * h) - 1.0;

    q = (R - D) / (U - D);
    b = false;

    BuildPriceTree();
}

void CRRPricer::BuildPriceTree() {
    price_tree.setDepth(depth);
    for (int n = 0; n <= depth; n++) {
        for (int j = 0; j <= n; j++) {
            double price = S0 * std::pow(1 + U, j) * std::pow(1 + D, n - j);
            price_tree.setNode(n, j, price);
        }
    }
}

void CRRPricer::compute() {
    option_tree.setDepth(depth);
    // AJOUT : on initialise aussi l’arbre d’exercice
    exercise_tree.setDepth(depth);

    // The leaf nodes are the payoff at expiry
    for (int i = 0; i <= depth; ++i) {
        double spot = price_tree.getNode(depth, i);
        
        double payoff_val = option->payoff(spot);
        option_tree.setNode(depth, i, option->payoff(spot));

        // AJOUT : à maturité, on considère que si payoff > 0, on exerce
        exercise_tree.setNode(depth, i, payoff_val > 0.0);
    }

    // Backward induction
    for (int n = depth - 1; n >= 0; --n) {
        for (int i = 0; i <= n; ++i) {
            double upVal = option_tree.getNode(n + 1, i + 1);
            double downVal = option_tree.getNode(n + 1, i);
            double continuation = (q * upVal + (1.0 - q) * downVal) / (1.0 + R);

            double spot = price_tree.getNode(n, i);
            double intrinsic = option->payoff(spot);

            double val;
            bool exercise = false;

            if (option->isAmericanOption()) {
                // AJOUT : règle H(n,i) = max(continuation, intrinsic)
                if (intrinsic >= continuation) {
                    val = intrinsic;
                    exercise = true;
                }
                else {
                    val = continuation;
                    exercise = false;
                }
            }
            else {
                // Comportement original pour les européennes
                val = continuation;
                exercise = false;
            }

            option_tree.setNode(n, i, val);
            // AJOUT : mémoriser la politique d’exercice pour ce nœud
            exercise_tree.setNode(n, i, exercise);
        }
    }

    b = true;
}

double CRRPricer::get(int n, int i) {
    if (n < 0 || n > depth) throw std::out_of_range("get: level n out of range");
    if (i < 0 || i > n) throw std::out_of_range("get: index i out of range for level n");
    return option_tree.getNode(n, i);
}

bool CRRPricer::getExercise(int n, int i) {
    if (n < 0 || n > depth) throw std::out_of_range("getExercise: level n out of range");
    if (i < 0 || i > n) throw std::out_of_range("getExercise: index i out of range for level n");
    return exercise_tree.getNode(n, i);
}

double CRRPricer::operator()(bool closed_form) {
    if (!closed_form) {
        if (!b) compute();
        return option_tree.getNode(0, 0);
    }

    double sum = 0.0;
    for (int i = 0; i <= depth; ++i) {
        double payoff = option->payoff(S0 * std::pow(1.0 + U, i) * std::pow(1.0 + D, depth - i));
        sum += (std::tgamma(depth+1) / (std::tgamma(i+1) * std::tgamma(depth - i+1))) * std::pow(q, i) * std::pow(1.0 - q, depth - i) * payoff;
    }

    return sum / std::pow(1.0 + R, depth);
}
