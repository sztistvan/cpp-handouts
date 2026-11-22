// Logistic population growth with plain variables.
// Simulation thread, version 1: everything in main, no functions, no containers.
#include <iomanip>
#include <iostream>

int main()
{
    const double r = 0.4;           // growth rate per generation
    const double capacity = 1000.0; // carrying capacity K
    double population = 10.0;       // N at generation 0
    const int generations = 25;

    std::cout << std::setw(5) << "gen" << std::setw(12) << "population" << '\n';
    std::cout << std::fixed << std::setprecision(1);
    for (int t = 0; t <= generations; ++t) {
        std::cout << std::setw(5) << t << std::setw(12) << population << '\n';
        population = population + r * population * (1.0 - population / capacity);
    }
    return 0;
}
