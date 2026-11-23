// Word frequencies in a text: a map counts, a vector and a lambda sort. The text is invented.
#include <algorithm>
#include <cctype>
#include <cstddef>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

// Keep only letters, in lower case: "Enzymes," becomes "enzymes".
std::string clean(const std::string& word)
{
    std::string result;
    for (char c : word) {
        if (std::isalpha(static_cast<unsigned char>(c))) {
            result.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(c))));
        }
    }
    return result;
}

int main()
{
    const std::string text =
        "The enzyme binds the substrate. The substrate is converted, and the product leaves the enzyme. "
        "A second substrate binds the free enzyme.";

    std::map<std::string, int> counts;
    std::istringstream stream(text);
    std::string word;
    int total = 0;
    while (stream >> word) {
        const std::string w = clean(word);
        if (!w.empty()) {
            ++counts[w];
            ++total;
        }
    }

    std::vector<std::pair<std::string, int>> ranking(counts.begin(), counts.end());
    std::sort(ranking.begin(), ranking.end(),
              [](const std::pair<std::string, int>& x, const std::pair<std::string, int>& y) {
                  if (x.second != y.second) {
                      return x.second > y.second;
                  }
                  return x.first < y.first;
              });

    std::cout << total << " words, " << counts.size() << " different\n\n";
    for (std::size_t i = 0; i < 5 && i < ranking.size(); ++i) {
        std::cout << "  " << ranking[i].first << ": " << ranking[i].second << '\n';
    }
    return 0;
}
