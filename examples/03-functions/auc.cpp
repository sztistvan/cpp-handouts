// Area under the curve (AUC) of measured drug concentrations with the trapezoid rule.
// The data are hypothetical, chosen only to illustrate the method.
#include <iostream>
#include <iterator>

// Sum of the trapezoids between neighboring measurements. Works for unevenly spaced times.
double auc_trapezoid(const double time[], const double concentration[], int n)
{
    double area = 0.0;
    for (int i = 1; i < n; ++i) {
        area += 0.5 * (concentration[i] + concentration[i - 1]) * (time[i] - time[i - 1]);
    }
    return area;
}

int main()
{
    const double time[] = {0.0, 0.5, 1.0, 2.0, 4.0, 6.0, 8.0, 12.0};          // h
    const double conc[] = {0.0, 4.1, 6.3, 7.2, 5.4, 3.6, 2.4, 1.1};           // mg/L
    const int n = static_cast<int>(std::size(time));

    // Highest measured concentration and when it occurred.
    double c_max = conc[0];
    double t_max = time[0];
    for (int i = 1; i < n; ++i) {
        if (conc[i] > c_max) {
            c_max = conc[i];
            t_max = time[i];
        }
    }

    std::cout << "Cmax = " << c_max << " mg/L at t = " << t_max << " h\n";
    std::cout << "AUC (0 to " << time[n - 1] << " h) = " << auc_trapezoid(time, conc, n) << " mg*h/L\n";
    return 0;
}
