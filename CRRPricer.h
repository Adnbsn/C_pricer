#pragma once
#include "Option.h"
#include "BinaryTree.h"
#include <stdexcept>

class CRRPricer
{
public:
    int depth;
    double S0;
    double U;
    double D;
    double R;
    double q; // risk-neutral probability
    BinaryTree<double> price_tree;
    Option* option;
    BinaryTree<double> option_tree;
    bool b = false;

    // AJOUT : arbre pour la politique d’exercice
    BinaryTree<bool> exercise_tree;

    // Constructor
    CRRPricer(Option* Option, int Depth, double asset_price, double up, double down, double interest_rate);


    // AJOUT : getter de la politique d’exercice
    bool getExercise(int n, int i);// const ;

    // AJOUT : constructeur Black–Scholes
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
