// Long-run behavior of the logistic model for many growth rates (the "bifurcation diagram").
// Prints CSV text (r,population) to the console; figures/make_figures.py turns it into a picture.
#include <iostream>

int main()
{
    const double capacity = 1000.0;

    std::cout << "r,population\n";
    for (int k = 0; k <= 480; ++k) {
        const double r = 0.5 + 0.005 * k; // r runs from 0.5 to 2.9

        double population = 10.0;
        for (int t = 0; t < 500; ++t) { // let the start-up phase pass
            population = population + r * population * (1.0 - population / capacity);
        }
        for (int t = 0; t < 100; ++t) { // record where the population keeps moving
            population = population + r * population * (1.0 - population / capacity);
            std::cout << r << ',' << population << '\n';
        }
    }
    return 0;
}
