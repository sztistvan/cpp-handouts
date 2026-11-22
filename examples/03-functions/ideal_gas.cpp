// The ideal gas law with a default argument: p = n R T / V
#include <iomanip>
#include <iostream>

const double gas_constant = 8.314462618; // J/(mol K), exact since the 2019 SI redefinition (to this precision)

// Pressure in pascal. The temperature is optional: 298.15 K (25 degrees C) if the caller omits it.
double pressure_pa(double moles, double volume_m3, double temperature_k = 298.15)
{
    return moles * gas_constant * temperature_k / volume_m3;
}

int main()
{
    std::cout << std::fixed << std::setprecision(3);

    // 1 mol in 22.414 L at 273.15 K: about one atmosphere (101.325 kPa).
    std::cout << "1 mol, 22.414 L, 273.15 K: " << pressure_pa(1.0, 0.022414, 273.15) / 1000.0 << " kPa\n";

    // Same amount in 24.465 L, temperature left out: the default 298.15 K is used.
    std::cout << "1 mol, 24.465 L, default T: " << pressure_pa(1.0, 0.024465) / 1000.0 << " kPa\n";

    // Warming the second case to 310.15 K (body temperature) in the same volume.
    std::cout << "1 mol, 24.465 L, 310.15 K: " << pressure_pa(1.0, 0.024465, 310.15) / 1000.0 << " kPa\n";
    return 0;
}
