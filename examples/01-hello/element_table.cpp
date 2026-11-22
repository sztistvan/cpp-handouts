// Elements of life: a formatted table, plus the molar mass of water.
#include <iomanip>
#include <iostream>
#include <string>

int main()
{
    // Header
    std::cout << std::left << std::setw(4) << "Z" << std::setw(8) << "Symbol"
              << std::setw(12) << "Name" << std::right << std::setw(8) << "Mass" << '\n';
    std::cout << std::string(32, '-') << '\n';

    // Five rows. Numbers: right-aligned, three decimals.
    std::cout << std::fixed << std::setprecision(3);
    std::cout << std::left << std::setw(4) << 1 << std::setw(8) << "H" << std::setw(12) << "Hydrogen"
              << std::right << std::setw(8) << 1.008 << '\n';
    std::cout << std::left << std::setw(4) << 6 << std::setw(8) << "C" << std::setw(12) << "Carbon"
              << std::right << std::setw(8) << 12.011 << '\n';
    std::cout << std::left << std::setw(4) << 7 << std::setw(8) << "N" << std::setw(12) << "Nitrogen"
              << std::right << std::setw(8) << 14.007 << '\n';
    std::cout << std::left << std::setw(4) << 8 << std::setw(8) << "O" << std::setw(12) << "Oxygen"
              << std::right << std::setw(8) << 15.999 << '\n';
    std::cout << std::left << std::setw(4) << 15 << std::setw(8) << "P" << std::setw(12) << "Phosphorus"
              << std::right << std::setw(8) << 30.974 << '\n';

    // A first calculation with named values (variables).
    const double mass_h = 1.008;
    const double mass_o = 15.999;
    const double water = 2 * mass_h + mass_o;

    std::cout << "\nMolar mass of H2O: " << water << " g/mol\n";
    return 0;
}
