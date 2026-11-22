// A table of squares and square roots (a first loop, covered properly in handout 2).
#include <cmath>
#include <iomanip>
#include <iostream>

int main()
{
    std::cout << std::setw(4) << "n" << std::setw(6) << "n^2" << std::setw(10) << "sqrt(n)" << '\n';
    std::cout << std::fixed << std::setprecision(4);
    for (int n = 1; n <= 10; ++n) {
        std::cout << std::setw(4) << n << std::setw(6) << n * n << std::setw(10) << std::sqrt(n) << '\n';
    }
    return 0;
}
