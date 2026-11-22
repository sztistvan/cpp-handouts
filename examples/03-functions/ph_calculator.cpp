// pH calculations as small functions.
#include <cmath>
#include <iomanip>
#include <iostream>

// pH = -log10([H+]) with the concentration in mol/L.
double ph_from_concentration(double h_concentration)
{
    return -std::log10(h_concentration);
}

// The inverse: [H+] = 10^(-pH).
double concentration_from_ph(double ph)
{
    return std::pow(10.0, -ph);
}

// Henderson-Hasselbalch: pH of a buffer made of a weak acid and its conjugate base.
double buffer_ph(double pka, double base_concentration, double acid_concentration)
{
    return pka + std::log10(base_concentration / acid_concentration);
}

int main()
{
    std::cout << std::setw(14) << "[H+] (mol/L)" << std::setw(8) << "pH" << '\n';
    const double concentrations[] = {1.0e-1, 1.0e-3, 1.0e-7, 3.2e-8, 1.0e-10};
    for (double c : concentrations) {
        std::cout << std::scientific << std::setprecision(1) << std::setw(14) << c
                  << std::fixed << std::setprecision(2) << std::setw(8) << ph_from_concentration(c) << '\n';
    }

    std::cout << "\npH 7.40 corresponds to [H+] = " << std::scientific << std::setprecision(2)
              << concentration_from_ph(7.40) << " mol/L\n\n";

    const double pka = 5.00; // a hypothetical weak acid
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Buffer with pKa = " << pka << ":\n";
    const double ratios[] = {0.1, 1.0, 10.0};
    for (double ratio : ratios) {
        std::cout << "  [base]/[acid] = " << std::setw(4) << ratio << "  ->  pH " << buffer_ph(pka, ratio, 1.0) << '\n';
    }
    return 0;
}
