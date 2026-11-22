// Same logistic model, several growth rates: what does the population do in the long run?
#include <iomanip>
#include <iostream>

int main()
{
    const double capacity = 1000.0;
    const double rates[] = {0.4, 1.8, 2.2, 2.5, 2.8};

    std::cout << std::fixed << std::setprecision(1);
    for (double r : rates) {
        double population = 10.0;
        for (int t = 0; t < 200; ++t) { // let the start-up phase pass
            population = population + r * population * (1.0 - population / capacity);
        }
        std::cout << "r = " << r << ": generations 200..207:";
        for (int t = 200; t < 208; ++t) {
            std::cout << std::setw(8) << population;
            population = population + r * population * (1.0 - population / capacity);
        }
        std::cout << '\n';
    }
    return 0;
}
