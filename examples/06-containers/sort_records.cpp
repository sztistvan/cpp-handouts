// Sorting records with lambdas. The data are the usable lines of measurements.csv (handout 5).
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

struct Sample {
    std::string id;
    std::string group;
    double rate;
};

void print(const std::string& title, const std::vector<Sample>& samples)
{
    std::cout << title << ":\n";
    for (const Sample& s : samples) {
        std::cout << "  " << s.id << "  " << std::left << std::setw(9) << s.group << std::right << s.rate << '\n';
    }
}

int main()
{
    std::vector<Sample> samples = {
        {"S01", "control", 98.2}, {"S02", "control", 101.5}, {"S03", "control", 99.8},
        {"S04", "control", 103.1}, {"S05", "treated", 112.4}, {"S06", "treated", 115.0},
        {"S08", "treated", 118.7}, {"S10", "control", 97.6},  {"S12", "treated", 121.3},
    };

    // 1. By rate, the largest first. The lambda says how two records are compared.
    std::sort(samples.begin(), samples.end(), [](const Sample& a, const Sample& b) { return a.rate > b.rate; });
    print("By rate, largest first", samples);

    // 2. By group, and inside a group by rate (smallest first).
    std::sort(samples.begin(), samples.end(), [](const Sample& a, const Sample& b) {
        if (a.group != b.group) {
            return a.group < b.group;
        }
        return a.rate < b.rate;
    });
    std::cout << '\n';
    print("By group, then by rate", samples);

    // 3. A lambda can use a variable of its surroundings: [threshold] "captures" it.
    const double threshold = 110.0;
    const auto high = std::count_if(samples.begin(), samples.end(),
                                    [threshold](const Sample& s) { return s.rate > threshold; });
    std::cout << "\nSamples with a rate above " << threshold << ": " << high << " of " << samples.size() << '\n';
    return 0;
}
