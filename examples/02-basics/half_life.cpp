// Radioactive decay of a hypothetical tracer, day by day, until 1 % is left.
#include <cmath>
#include <iostream>

int main()
{
    const double half_life = 8.0;    // days
    const double start_amount = 100.0; // mg
    const double limit = 1.0;        // mg, which is 1 % of the start

    const double daily_factor = std::pow(0.5, 1.0 / half_life); // fraction left after one day

    double amount = start_amount;
    int days = 0;
    while (amount > limit) {
        amount *= daily_factor;
        ++days;
    }

    std::cout << "Daily factor:          " << daily_factor << '\n';
    std::cout << "Days until <= 1 mg:    " << days << " (loop)\n";
    std::cout << "Exact time to 1 mg:    " << half_life * std::log2(start_amount / limit) << " days (formula)\n";
    std::cout << "Amount after " << days << " days: " << amount << " mg\n";
    return 0;
}
