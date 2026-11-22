// Michaelis-Menten enzyme kinetics: reaction rate versus substrate concentration.
#include <iomanip>
#include <iostream>

// Reaction rate v for substrate concentration s: v = vmax * s / (km + s)
double michaelis_menten(double vmax, double km, double substrate)
{
    return vmax * substrate / (km + substrate);
}

// The inverse: which substrate concentration gives the rate v? (needs 0 <= v < vmax)
double substrate_for_rate(double vmax, double km, double rate)
{
    return km * rate / (vmax - rate);
}

int main()
{
    const double vmax = 100.0; // umol/min
    const double km = 2.5;     // mM

    const double substrate[] = {0.1, 0.25, 0.5, 1.0, 2.5, 5.0, 10.0, 25.0, 50.0, 100.0};

    std::cout << std::setw(8) << "S (mM)" << std::setw(14) << "v (umol/min)" << std::setw(10) << "v/Vmax" << '\n';
    std::cout << std::fixed;
    for (double s : substrate) {
        const double v = michaelis_menten(vmax, km, s);
        std::cout << std::setprecision(2) << std::setw(8) << s << std::setw(14) << v
                  << std::setprecision(3) << std::setw(10) << v / vmax << '\n';
    }

    std::cout << std::setprecision(2);
    std::cout << "\nAt S = Km = " << km << " mM the rate is " << michaelis_menten(vmax, km, km) << " umol/min (half of Vmax)\n";
    std::cout << "90 % of Vmax needs S = " << substrate_for_rate(vmax, km, 0.9 * vmax) << " mM (9 times Km)\n";
    return 0;
}
