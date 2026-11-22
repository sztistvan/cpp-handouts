// Newton's method for square roots: how fast does a good algorithm converge?
#include <cmath>
#include <iomanip>
#include <iostream>

// One improvement step for the guess x of sqrt(a).
double newton_step(double x, double a)
{
    return 0.5 * (x + a / x);
}

// Repeat steps until the guess stops changing by more than the tolerance.
// Both tolerance and max_iterations have default values.
double newton_sqrt(double a, double tolerance = 1.0e-12, int max_iterations = 50)
{
    double x = a;
    for (int i = 0; i < max_iterations; ++i) {
        const double next = newton_step(x, a);
        if (std::abs(next - x) < tolerance) {
            return next;
        }
        x = next;
    }
    return x;
}

int main()
{
    const double a = 2.0;
    const double exact = std::sqrt(a);

    std::cout << "Steps of Newton's method for sqrt(" << a << "), starting at x = " << a << ":\n";
    std::cout << std::setw(6) << "step" << std::setw(20) << "x" << std::setw(14) << "error" << '\n';
    double x = a;
    for (int step = 0; step <= 5; ++step) {
        std::cout << std::setw(6) << step << std::fixed << std::setprecision(15) << std::setw(20) << x
                  << std::scientific << std::setprecision(2) << std::setw(14) << std::abs(x - exact) << '\n';
        x = newton_step(x, a);
    }

    std::cout << std::fixed << std::setprecision(12);
    std::cout << "\nnewton_sqrt(2)           = " << newton_sqrt(2.0) << '\n';
    std::cout << "newton_sqrt(2, 1e-3)     = " << newton_sqrt(2.0, 1.0e-3) << "  (looser tolerance)\n";
    std::cout << "newton_sqrt(1e6)         = " << newton_sqrt(1.0e6) << '\n';
    return 0;
}
