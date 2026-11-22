// The element table of handout 1, now with the data in vectors and one loop.
// Same problem, new tool: the output is identical to element_table.cpp.
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    const std::vector<int> numbers = {1, 6, 7, 8, 15};
    const std::vector<std::string> symbols = {"H", "C", "N", "O", "P"};
    const std::vector<std::string> names = {"Hydrogen", "Carbon", "Nitrogen", "Oxygen", "Phosphorus"};
    const std::vector<double> masses = {1.008, 12.011, 14.007, 15.999, 30.974};

    // Header
    std::cout << std::left << std::setw(4) << "Z" << std::setw(8) << "Symbol" << std::setw(12) << "Name"
              << std::right << std::setw(8) << "Mass" << '\n';
    std::cout << std::string(32, '-') << '\n';

    // One loop instead of five copies.
    std::cout << std::fixed << std::setprecision(3);
    for (std::size_t i = 0; i < numbers.size(); ++i) {
        std::cout << std::left << std::setw(4) << numbers[i] << std::setw(8) << symbols[i] << std::setw(12)
                  << names[i] << std::right << std::setw(8) << masses[i] << '\n';
    }

    // Hydrogen is entry 0 and oxygen entry 3. (Fragile: see the handout.)
    const double water = 2 * masses[0] + masses[3];
    std::cout << "\nMolar mass of H2O: " << water << " g/mol\n";
    return 0;
}
