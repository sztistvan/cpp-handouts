// Writing simulation results to a CSV file, then reading the first lines back.
// Simulation thread, version 4: the results leave the program, for plotting or other tools.
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#ifndef OUTPUT_DIR
#define OUTPUT_DIR "."
#endif

double logistic_step(double population, double r, double capacity)
{
    return population + r * population * (1.0 - population / capacity);
}

int main()
{
    const std::string path = std::string(OUTPUT_DIR) + "/logistic.csv";
    const double capacity = 1000.0;
    const double rates[3] = {0.2, 0.4, 0.8};
    const int generations = 30;

    std::ofstream out(path);
    if (!out) {
        std::cerr << "Cannot write logistic.csv\n";
        return 1;
    }
    out << std::fixed << std::setprecision(3);
    out << "generation,r_0.2,r_0.4,r_0.8\n";

    double population[3] = {10.0, 10.0, 10.0};
    for (int t = 0; t <= generations; ++t) {
        out << t;
        for (int k = 0; k < 3; ++k) {
            out << ',' << population[k];
            population[k] = logistic_step(population[k], rates[k], capacity);
        }
        out << '\n';
    }
    out.close(); // make sure everything is written before we read the file again

    std::cout << "Wrote " << generations + 1 << " data rows to logistic.csv\n\n";

    // Read it back, as a check.
    std::ifstream in(path);
    std::string line;
    int count = 0;
    std::cout << "First lines of the file:\n";
    while (std::getline(in, line)) {
        if (count < 5) {
            std::cout << "  " << line << '\n';
        }
        ++count;
    }
    std::cout << "Lines in the file: " << count << " (1 header + " << count - 1 << " data rows)\n";
    return 0;
}
