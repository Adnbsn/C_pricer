#include "MT.h"
#include <chrono>

// Static member initialization
std::mt19937 MT::generator;
bool MT::initialized = false;


// This method checks that the generator has been initialized only once and initializes its seed with the current time to ensure we get different sequences of numbers for different times
void MT::initialize()
{
    if (!initialized)
    {
        // Seed with current time
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        generator.seed(seed);
        initialized = true;
    }
}

// to generate numbers following a uniform distribution
double MT::rand_unif()
{
    initialize();  // Ensure generator is initialized

    // Uniform distribution [0, 1]
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

// to generate numbers following a normal distribution
double MT::rand_norm()
{
    initialize();  // Ensure generator is initialized

    // Normal distribution N(0, 1)
    std::normal_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);

}
