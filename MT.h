#pragma once
#include <random>

class MT
{
private:
    // Static instance of the random generator
    static std::mt19937 generator;

    // Flag to ensure generator is initialized only once
    static bool initialized;

    // Private constructor to prevent instantiation
    MT() = delete;

    // Delete copy constructor and assignment operator
    MT(const MT&) = delete;
    MT& operator=(const MT&) = delete;

    // Initialize the generator (called once)
    static void initialize();

public:
    // Generate uniform random number in [0, 1]
    static double rand_unif();

    // Generate normal random number N(0, 1)
    static double rand_norm();
};
