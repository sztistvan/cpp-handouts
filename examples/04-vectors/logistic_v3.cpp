// Logistic population growth, version 3: the whole history is kept in a vector.
// Simulation thread: because the numbers are stored, they can be analysed afterwards.
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <vector>

double logistic_step(double population, double r, double capacity)
{
    return population + r * population * (1.0 - population / capacity);
}

int main()
{
    const double r = 0.4;
    const double capacity = 1000.0;
    const int generations = 25;

    // population[t] is the population in generation t.
    std::vector<double> population;
    population.push_back(10.0);
    for (int t = 0; t < generations; ++t) {
        population.push_back(logistic_step(population.back(), r, capacity));
    }

    // growth[t] is the increase from generation t to t + 1.
    std::vector<double> growth;
    for (std::size_t t = 0; t + 1 < population.size(); ++t) {
        growth.push_back(population[t + 1] - population[t]);
    }

    std::cout << std::fixed << std::setprecision(1);
    std::cout << std::setw(5) << "gen" << std::setw(12) << "population" << std::setw(10) << "growth" << '\n';
    for (std::size_t t = 0; t < population.size(); ++t) {
        std::cout << std::setw(5) << t << std::setw(12) << population[t];
        if (t < growth.size()) {
            std::cout << std::setw(10) << growth[t];
        } else {
            std::cout << std::setw(10) << "-";
        }
        std::cout << '\n';
    }

    // Questions that need the whole history:
    std::size_t first_above = 0;
    while (population[first_above] < 0.9 * capacity) {
        ++first_above;
    }

    std::size_t fastest = 0;
    for (std::size_t t = 1; t < growth.size(); ++t) {
        if (growth[t] > growth[fastest]) {
            fastest = t;
        }
    }

    std::cout << "\nFirst generation with N >= 90 % of K: " << first_above << '\n';
    std::cout << "Largest growth per generation: " << growth[fastest] << " (generation " << fastest << " to "
              << fastest + 1 << ", starting at N = " << population[fastest] << ")\n";
    return 0;
}
