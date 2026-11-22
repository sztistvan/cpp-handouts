// The Collatz (3n+1) problem: how many steps until a number reaches 1?
#include <iostream>

int main()
{
    int best_start = 1;
    int best_steps = 0;

    for (int start = 1; start <= 30; ++start) {
        long long n = start;
        int steps = 0;
        while (n != 1) {
            if (n % 2 == 0) {
                n /= 2;
            } else {
                n = 3 * n + 1;
            }
            ++steps;
        }
        if (steps > best_steps) {
            best_steps = steps;
            best_start = start;
        }
    }
    std::cout << "Longest chain below 31 starts at " << best_start << " with " << best_steps << " steps\n";

    // Follow that chain and record its highest value.
    long long n = best_start;
    long long peak = n;
    while (n != 1) {
        n = (n % 2 == 0) ? n / 2 : 3 * n + 1;
        if (n > peak) {
            peak = n;
        }
    }
    std::cout << "Highest value on the way: " << peak << '\n';
    return 0;
}
