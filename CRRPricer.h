#pragma once
#include "Option.h"
#include "BinaryTree.h"
#include <stdexcept>

/*
CRRPricer implements the Cox–Ross–Rubinstein (CRR) binomial model for option pricing
It supports European options and American options with early exercise
The model approximates the Black–Scholes dynamics by a discrete-time recombining tree
and converges to the continuous-time price.
*/

class CRRPricer
{
public:
    int depth; // Number of time steps in the binomial tree
    double S0; // Initial underlying price
    double U;  // Up factor
    double D;  // Down factor
    double R;  // Risk-free growth factor per step
    double q;  // risk-neutral probability
    BinaryTree<double> price_tree;
    Option* option;
    BinaryTree<double> option_tree;
    bool b = false;

    // EXERCISE POLICY FOR AMERICAN OPTIONS
    BinaryTree<bool> exercise_tree;

    /* CRR constructor with explicit binomial parameters:
     U : up factor
     D : down factor
     R : risk-free growth factor
    */

    // Constructor
    CRRPricer(Option* Option, int Depth, double asset_price, double up, double down, double interest_rate);


    /* Getter for the exercise policy returns true if early exercise is optimal at node (n,i)
    Only used for American options
    */
    bool getExercise(int n, int i);

    /* Constructor using Black–Scholes parameters:
    r: continuously compounded risk-free rate
    sigma: volatility
    To convert (r, sigma) into CRR parameters (U, D, q)
    */

    CRRPricer(Option* option, int depth, double asset_price, double r, double volatility);

    // Build the stock price tree
    void BuildPriceTree();

    // Compute option tree using CRR backward induction
    void compute();

    // Getter H(n,i)
    double get(int n, int i);

    // Option price
    double operator()(bool closed_form = false);

};
