// Reading a FASTA file: records that start with '>' and continue over several lines of sequence.
#include <cstddef>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#ifndef DATA_DIR
#define DATA_DIR "data"
#endif

double gc_content(const std::string& dna)
{
    int gc = 0;
    int known = 0;
    for (char c : dna) {
        if (c == 'G' || c == 'C') {
            ++gc;
        }
        if (c == 'A' || c == 'C' || c == 'G' || c == 'T') {
            ++known;
        }
    }
    return known == 0 ? 0.0 : static_cast<double>(gc) / known;
}

int main()
{
    const std::string path = std::string(DATA_DIR) + "/sequences.fasta";
    std::ifstream in(path);
    if (!in) {
        std::cerr << "Cannot open " << path << '\n';
        return 1;
    }

    // Two parallel vectors (see handout 4): ids[i] belongs to sequences[i].
    std::vector<std::string> ids;
    std::vector<std::string> sequences;

    std::string line;
    while (std::getline(in, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (line.empty()) {
            continue;
        }
        if (line[0] == '>') { // header line: a new record starts
            std::istringstream header(line.substr(1));
            std::string id;
            header >> id; // the first word is the identifier
            ids.push_back(id);
            sequences.push_back("");
        } else if (!sequences.empty()) {
            sequences.back() += line; // a sequence line: append to the current record
        } else {
            std::cerr << "Sequence data before the first header line\n";
            return 1;
        }
    }

    std::cout << "sequences.fasta: " << ids.size() << " records\n\n";
    std::cout << std::left << std::setw(8) << "id" << std::right << std::setw(8) << "length" << std::setw(8) << "GC %"
              << '\n';
    std::cout << std::fixed << std::setprecision(1);
    for (std::size_t i = 0; i < ids.size(); ++i) {
        std::cout << std::left << std::setw(8) << ids[i] << std::right << std::setw(8) << sequences[i].size()
                  << std::setw(8) << 100.0 * gc_content(sequences[i]) << '\n';
    }
    return 0;
}
