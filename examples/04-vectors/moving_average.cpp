// Moving average: smoothing a noisy measurement series. The data are invented.
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <vector>

// Average of every `window` consecutive values. The result has size() - window + 1 elements.
std::vector<double> moving_average(const std::vector<double>& values, std::size_t window)
{
    std::vector<double> result;
    if (window == 0 || window > values.size()) {
        return result; // nothing sensible to compute: return an empty vector
    }
    for (std::size_t start = 0; start + window <= values.size(); ++start) {
        double sum = 0.0;
        for (std::size_t k = 0; k < window; ++k) {
            sum += values[start + k];
        }
        result.push_back(sum / static_cast<double>(window));
    }
    return result;
}

int main()
{
    const std::vector<double> signal = {2.1, 2.9, 2.4, 3.6, 3.1, 4.4, 3.8, 5.2, 4.9, 5.5};
    const std::vector<double> smooth = moving_average(signal, 3);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "raw (" << signal.size() << " values):     ";
    for (double v : signal) {
        std::cout << std::setw(6) << v;
    }
    std::cout << "\nsmoothed (" << smooth.size() << " values): ";
    for (double v : smooth) {
        std::cout << std::setw(6) << v;
    }
    std::cout << '\n';
    return 0;
}
