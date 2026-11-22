// Mean, sample standard deviation and median of repeated measurements.
// The data are hypothetical: nine replicates of an enzyme rate (umol/min), the last one an outlier.
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <vector>

double mean(const std::vector<double>& values)
{
    double sum = 0.0;
    for (double v : values) {
        sum += v;
    }
    return sum / static_cast<double>(values.size());
}

// Sample standard deviation (divide by n - 1). Two passes: first the mean, then the squared deviations.
double standard_deviation(const std::vector<double>& values)
{
    const double m = mean(values);
    double sum_of_squares = 0.0;
    for (double v : values) {
        sum_of_squares += (v - m) * (v - m);
    }
    return std::sqrt(sum_of_squares / static_cast<double>(values.size() - 1));
}

// Median: the middle value of the sorted data.
// The parameter is a COPY (not a reference) on purpose: sorting must not reorder the caller's data.
double median(std::vector<double> values)
{
    std::sort(values.begin(), values.end());
    const std::size_t n = values.size();
    if (n % 2 == 1) {
        return values[n / 2];
    }
    return 0.5 * (values[n / 2 - 1] + values[n / 2]);
}

void print_summary(const char* label, const std::vector<double>& values)
{
    std::cout << std::left << std::setw(18) << label << std::right << "n = " << values.size()
              << "   mean = " << mean(values) << "   SD = " << standard_deviation(values)
              << "   median = " << median(values) << '\n';
}

int main()
{
    const std::vector<double> data = {98.2, 101.5, 99.8, 103.1, 97.6, 100.4, 102.2, 99.1, 124.0};

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Data (" << data.size() << " values):";
    for (double v : data) {
        std::cout << ' ' << v;
    }
    std::cout << '\n';
    print_summary("All values:", data);

    // Leave out the suspicious value and compare.
    std::vector<double> cleaned;
    for (double v : data) {
        if (v < 110.0) {
            cleaned.push_back(v);
        }
    }
    print_summary("Without outlier:", cleaned);
    return 0;
}
