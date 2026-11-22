// Fibonacci's rabbits: pairs per month, and how the growth ratio settles down.
#include <iomanip>
#include <iostream>

int main()
{
    long long previous = 1; // pairs last month
    long long current = 1;  // pairs this month

    std::cout << std::setw(6) << "month" << std::setw(14) << "pairs" << std::setw(10) << "ratio" << '\n';
    std::cout << std::fixed << std::setprecision(6);
    for (int month = 1; month <= 30; ++month) {
        if (month <= 10 || month % 5 == 0) { // print only some rows
            std::cout << std::setw(6) << month << std::setw(14) << current << std::setw(10)
                      << static_cast<double>(current) / static_cast<double>(previous) << '\n';
        }
        const long long next = previous + current;
        previous = current;
        current = next;
    }
    return 0;
}
