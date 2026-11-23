// Counting k-mers (all substrings of length k) in DNA sequences read from a FASTA file.
// "Same problem, new tool": a struct replaces the parallel vectors of handout 5.
#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#ifndef DATA_DIR
#define DATA_DIR "data"
#endif

// One record of a FASTA file: the identifier and the sequence belong together.
struct Record {
    std::string id;
    std::string sequence;
};

std::vector<Record> read_fasta(const std::string& path)
{
    std::vector<Record> records;
    std::ifstream in(path);
    if (!in) {
        std::cerr << "Cannot open " << path << '\n';
        return records;
    }
    std::string line;
    while (std::getline(in, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (line.empty()) {
            continue;
        }
        if (line[0] == '>') {
            std::istringstream header(line.substr(1));
            Record record;
            header >> record.id;
            records.push_back(record);
        } else if (!records.empty()) {
            records.back().sequence += line;
        }
    }
    return records;
}

// How often does each k-mer occur? The map keeps the k-mers sorted alphabetically.
std::map<std::string, int> count_kmers(const std::string& dna, std::size_t k)
{
    std::map<std::string, int> counts;
    for (std::size_t i = 0; i + k <= dna.size(); ++i) {
        ++counts[dna.substr(i, k)];
    }
    return counts;
}

int main()
{
    const std::size_t k = 3;
    const std::vector<Record> records = read_fasta(std::string(DATA_DIR) + "/sequences.fasta");

    int possible = 1; // 4^k different k-mers exist
    for (std::size_t i = 0; i < k; ++i) {
        possible *= 4;
    }

    std::cout << "k = " << k << ": " << possible << " different " << k << "-mers are possible\n";
    for (const Record& record : records) {
        const std::map<std::string, int> counts = count_kmers(record.sequence, k);

        // A map is sorted by key. To sort by count, copy the entries into a vector and sort that.
        std::vector<std::pair<std::string, int>> ranking(counts.begin(), counts.end());
        std::sort(ranking.begin(), ranking.end(),
                  [](const std::pair<std::string, int>& x, const std::pair<std::string, int>& y) {
                      if (x.second != y.second) {
                          return x.second > y.second; // larger count first
                      }
                      return x.first < y.first;       // equal counts: alphabetical
                  });

        std::cout << "\n" << record.id << " (" << record.sequence.size() << " bases, "
                  << record.sequence.size() - k + 1 << " windows): " << counts.size() << " different " << k
                  << "-mers\n  most frequent:";
        for (std::size_t i = 0; i < 4 && i < ranking.size(); ++i) {
            std::cout << "  " << ranking[i].first << " x" << ranking[i].second;
        }
        std::cout << '\n';
    }
    return 0;
}
