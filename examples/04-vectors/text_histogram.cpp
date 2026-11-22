// A histogram drawn with text: how are the measurements distributed? The data are invented.
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    // Body masses of 24 mice in grams.
    const std::vector<double> masses = {21.3, 24.8, 22.5, 27.1, 25.6, 23.9, 26.4, 28.7, 24.1, 25.0, 26.8, 22.9,
                                        25.5, 27.6, 24.4, 23.2, 29.9, 26.1, 25.3, 24.7, 22.1, 28.2, 25.8, 26.6};

    const double low = 20.0;
    const double width = 2.0;
    const std::size_t bins = 5; // 20-22, 22-24, 24-26, 26-28, 28-30

    std::vector<int> counts(bins, 0);
    for (double m : masses) {
        if (m < low) {
            continue; // below the first bin (a negative number must not become an index)
        }
        const std::size_t bin = static_cast<std::size_t>((m - low) / width);
        if (bin < bins) { // ignore values above the last bin
            ++counts[bin];
        }
    }

    std::cout << std::fixed << std::setprecision(0);
    for (std::size_t b = 0; b < bins; ++b) {
        const double from = low + static_cast<double>(b) * width;
        std::cout << std::setw(3) << from << " - " << std::setw(2) << from + width << " g | "
                  << std::string(static_cast<std::size_t>(counts[b]), '*') << ' ' << counts[b] << '\n';
    }
    return 0;
}
