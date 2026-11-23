// The element table once more: one record per element, and a map for looking up a mass by symbol.
// Same problem, new tool: the output is identical to element_table.cpp and element_table_v2.cpp.
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct Element {
    int number;
    std::string symbol;
    std::string name;
    double mass;
};

int main()
{
    const std::vector<Element> elements = {
        {1, "H", "Hydrogen", 1.008},   {6, "C", "Carbon", 12.011},      {7, "N", "Nitrogen", 14.007},
        {8, "O", "Oxygen", 15.999},    {15, "P", "Phosphorus", 30.974},
    };

    // Header
    std::cout << std::left << std::setw(4) << "Z" << std::setw(8) << "Symbol" << std::setw(12) << "Name"
              << std::right << std::setw(8) << "Mass" << '\n';
    std::cout << std::string(32, '-') << '\n';

    std::cout << std::fixed << std::setprecision(3);
    for (const Element& e : elements) {
        std::cout << std::left << std::setw(4) << e.number << std::setw(8) << e.symbol << std::setw(12) << e.name
                  << std::right << std::setw(8) << e.mass << '\n';
    }

    // Look up masses by symbol: no more "entry 0 is hydrogen".
    std::map<std::string, double> mass_of;
    for (const Element& e : elements) {
        mass_of[e.symbol] = e.mass;
    }
    const double water = 2 * mass_of.at("H") + mass_of.at("O");
    std::cout << "\nMolar mass of H2O: " << water << " g/mol\n";
    return 0;
}
