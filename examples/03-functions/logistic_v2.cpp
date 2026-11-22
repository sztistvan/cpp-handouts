// Logistic population growth, version 2: the update rule is a function.
// Simulation thread: same numbers as version 1 (handout 2), but reusable.
#include <iomanip>
#include <iostream>

// One generation: the formula of version 1, now with a name.
double logistic_step(double population, double r, double capacity)
{
    return population + r * population * (1.0 - population / capacity);
}

// Run several generations and return the final population.
double population_after(double start, double r, double capacity, int generations)
{
    double population = start;
    for (int t = 0; t < generations; ++t) {
        population = logistic_step(population, r, capacity);
    }
    return population;
}

int main()
{
    const double r = 0.4;
    const double capacity = 1000.0;
    double population = 10.0;
    const int generations = 25;

    // Exactly the table of version 1.
    std::cout << std::setw(5) << "gen" << std::setw(12) << "population" << '\n';
    std::cout << std::fixed << std::setprecision(1);
    for (int t = 0; t <= generations; ++t) {
        std::cout << std::setw(5) << t << std::setw(12) << population << '\n';
        population = logistic_step(population, r, capacity);
    }

    // The payoff: other scenarios need one line each, not a copied loop.
    std::cout << "\nPopulation after 25 generations (start 10, K = 1000):\n";
    const double rates[] = {0.2, 0.4, 0.8};
    for (double rate : rates) {
        std::cout << "  r = " << std::setprecision(1) << rate << ": " << population_after(10.0, rate, capacity, 25) << '\n';
    }
    return 0;
}
