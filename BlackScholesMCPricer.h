#pragma once
#include "Option.h"
#include <vector>

class BlackScholesMCPricer
{
protected:
	Option* option;
	double initial_price;
	double interest_rate;
	double volatility;
	int nbPaths;

	// Current estimate statistics
	double sum_payoffs;        // Sum of all payoffs
	double sum_payoffs_squared; // Sum of squared payoffs
	int nb_paths_generated;     // Number of paths for this instance

public:
	//Constructor
	BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility);

	//Getter Number of paths
	int getNbPaths() const;

	// Generate number of paths method
	void generate(int nb_paths);

	//operator method
	double operator() () const;

	//confidence interval at 95%
	std::vector<double> confidenceInterval() const;
};

