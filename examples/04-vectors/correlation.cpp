// Pearson correlation coefficient of two series. The data are invented.
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <vector>

double mean(const std::vector<double>& values)
{
    double sum = 0.0;
    for (double v : values) {
        sum += v;
    }
    return sum / static_cast<double>(values.size());
}

// r = sum((x - mean_x) * (y - mean_y)) / sqrt(sum((x - mean_x)^2) * sum((y - mean_y)^2))
// Both vectors must have the same length (this function does not check it).
double correlation(const std::vector<double>& x, const std::vector<double>& y)
{
    const double mx = mean(x);
    const double my = mean(y);
    double sxy = 0.0;
    double sxx = 0.0;
    double syy = 0.0;
    for (std::size_t i = 0; i < x.size(); ++i) {
        sxy += (x[i] - mx) * (y[i] - my);
        sxx += (x[i] - mx) * (x[i] - mx);
        syy += (y[i] - my) * (y[i] - my);
    }
    return sxy / std::sqrt(sxx * syy);
}

int main()
{
    const std::vector<double> dose = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    const std::vector<double> response = {2.3, 3.1, 4.8, 5.2, 7.1, 7.4, 9.2, 9.6};
    const std::vector<double> noise = {5.1, 2.2, 6.7, 3.0, 4.4, 6.1, 2.9, 5.5};

    std::vector<double> falling;
    for (double r : response) {
        falling.push_back(20.0 - r); // the same data, upside down
    }

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "dose vs response:        r = " << correlation(dose, response) << '\n';
    std::cout << "dose vs 20 - response:   r = " << correlation(dose, falling) << '\n';
    std::cout << "dose vs unrelated noise: r = " << correlation(dose, noise) << '\n';
    return 0;
}
