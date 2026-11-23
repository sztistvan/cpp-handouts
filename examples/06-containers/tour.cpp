// A quick tour: records (struct), map, set, queue, priority_queue, sorting algorithms and lambdas.
#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <vector>

// A record: several named fields that belong together.
struct Sample {
    std::string id;
    double rate;
};

int main()
{
    // --- struct ---
    Sample a = {"S01", 98.2};
    std::cout << a.id << ": " << a.rate << '\n';
    std::vector<Sample> samples = {{"S01", 98.2}, {"S02", 101.5}, {"S03", 99.8}, {"S04", 103.1}};
    std::cout << "samples: " << samples.size() << ", last: " << samples.back().id << '\n';

    // --- map: key -> value, kept sorted by key ---
    const std::vector<std::string> codons = {"ATG", "GCC", "ATG", "TAA", "ATG", "GCC"};
    std::map<std::string, int> counts;
    for (const std::string& codon : codons) {
        ++counts[codon]; // a missing key is created with the value 0 first
    }
    std::cout << "\ncodon counts:\n";
    for (const auto& entry : counts) { // each entry has .first (the key) and .second (the value)
        std::cout << "  " << entry.first << " -> " << entry.second << '\n';
    }
    std::cout << "count(\"ATG\") = " << counts.count("ATG") << ", count(\"XYZ\") = " << counts.count("XYZ")
              << ", size = " << counts.size() << ", at(\"TAA\") = " << counts.at("TAA") << '\n';

    // --- set: every value once, sorted ---
    const std::set<std::string> unique(codons.begin(), codons.end());
    std::cout << "\n" << codons.size() << " codons, " << unique.size() << " different:";
    for (const std::string& codon : unique) {
        std::cout << ' ' << codon;
    }
    std::cout << '\n';

    // --- queue: first in, first out ---
    std::queue<int> line;
    line.push(1);
    line.push(2);
    line.push(3);
    std::cout << "\nqueue:";
    while (!line.empty()) {
        std::cout << ' ' << line.front();
        line.pop();
    }
    std::cout << '\n';

    // --- priority queue: the largest first, or the smallest first ---
    std::priority_queue<int> largest_first;
    std::priority_queue<int, std::vector<int>, std::greater<int>> smallest_first;
    for (int x : {5, 1, 8, 3}) {
        largest_first.push(x);
        smallest_first.push(x);
    }
    std::cout << "largest first: ";
    while (!largest_first.empty()) {
        std::cout << largest_first.top() << ' ';
        largest_first.pop();
    }
    std::cout << "\nsmallest first: ";
    while (!smallest_first.empty()) {
        std::cout << smallest_first.top() << ' ';
        smallest_first.pop();
    }
    std::cout << '\n';

    // --- algorithms work on a range given by begin() and end() ---
    std::vector<double> v = {3.2, 1.5, 4.8, 2.1, 1.5};
    std::sort(v.begin(), v.end());
    std::cout << "\nsorted:";
    for (double x : v) {
        std::cout << ' ' << x;
    }
    std::cout << "\ncount of 1.5: " << std::count(v.begin(), v.end(), 1.5);
    std::cout << "\ncontains 4.8: " << (std::find(v.begin(), v.end(), 4.8) != v.end());
    std::cout << "\nlargest: " << *std::max_element(v.begin(), v.end());
    std::cout << "\nsum: " << std::accumulate(v.begin(), v.end(), 0.0) << '\n';

    // --- lambda: a small function written where it is used ---
    std::sort(samples.begin(), samples.end(), [](const Sample& x, const Sample& y) { return x.rate > y.rate; });
    std::cout << "\nby rate, largest first:";
    for (const Sample& s : samples) {
        std::cout << ' ' << s.id << '(' << s.rate << ')';
    }
    const double threshold = 100.0;
    const auto above = std::count_if(samples.begin(), samples.end(),
                                     [threshold](const Sample& s) { return s.rate > threshold; });
    std::cout << "\nsamples above " << threshold << ": " << above << '\n';
    return 0;
}
