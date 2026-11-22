// Numerical integration with the trapezoid rule, tested against a known exact result.
// Problem: drug concentration C(t) = C0 * exp(-k t). What is the area under the curve from 0 to T?
#include <cmath>
#include <iomanip>
#include <iostream>

const double initial_concentration = 10.0; // mg/L
const double rate_constant = 0.3;          // 1/h

// The function to integrate.
double concentration(double t)
{
    return initial_concentration * std::exp(-rate_constant * t);
}

// Trapezoid rule: split [a, b] into n strips of width h and add up the trapezoid areas.
double trapezoid(double a, double b, int n)
{
    const double h = (b - a) / n;
    double sum = 0.5 * (concentration(a) + concentration(b)); // the two end points count half
    for (int i = 1; i < n; ++i) {
        sum += concentration(a + i * h);
    }
    return sum * h;
}

int main()
{
    const double T = 10.0; // hours
    const double exact = initial_concentration / rate_constant * (1.0 - std::exp(-rate_constant * T));

    std::cout << "Exact area 0.." << T << " h: " << std::setprecision(8) << exact << " mg*h/L\n\n";
    std::cout << std::setw(6) << "n" << std::setw(14) << "area" << std::setw(12) << "error" << std::setw(10) << "ratio" << '\n';

    double previous_error = 0.0;
    for (int n = 1; n <= 1024; n *= 2) {
        const double area = trapezoid(0.0, T, n);
        const double error = std::abs(area - exact);

        std::cout << std::fixed << std::setprecision(6) << std::setw(6) << n << std::setw(14) << area;
        std::cout << std::scientific << std::setprecision(3) << std::setw(12) << error;
        if (n == 1) {
            std::cout << std::setw(10) << "-";
        } else {
            std::cout << std::fixed << std::setprecision(2) << std::setw(10) << previous_error / error;
        }
        std::cout << '\n';
        previous_error = error;
    }
    return 0;
}
