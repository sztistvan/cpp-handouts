// Finding the recognition sites of restriction enzymes in a DNA sequence.
// The sequence is invented for this example.
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

char complement(char base)
{
    if (base == 'A') {
        return 'T';
    }
    if (base == 'T') {
        return 'A';
    }
    if (base == 'C') {
        return 'G';
    }
    if (base == 'G') {
        return 'C';
    }
    return 'N';
}

std::string reverse_complement(const std::string& dna)
{
    std::string result;
    for (std::size_t i = dna.size(); i > 0; --i) {
        result.push_back(complement(dna[i - 1]));
    }
    return result;
}

// All positions (counted from 0) where pattern occurs in text. Overlapping hits are found too.
std::vector<std::size_t> find_all(const std::string& text, const std::string& pattern)
{
    std::vector<std::size_t> positions;
    std::size_t pos = text.find(pattern);
    while (pos != std::string::npos) {
        positions.push_back(pos);
        pos = text.find(pattern, pos + 1); // continue just after the previous hit
    }
    return positions;
}

int main()
{
    const std::string dna = "CCGAATTCTTAGGATCCAAGCTTGGAATTCAATTGGATCCGA";
    const std::string enzymes[] = {"EcoRI", "BamHI", "HindIII"};
    const std::string sites[] = {"GAATTC", "GGATCC", "AAGCTT"};

    std::cout << "Sequence (" << dna.size() << " bases): " << dna << "\n\n";
    for (int k = 0; k < 3; ++k) {
        const std::vector<std::size_t> hits = find_all(dna, sites[k]);
        std::cout << enzymes[k] << " (" << sites[k] << ")"
                  << (reverse_complement(sites[k]) == sites[k] ? ", palindromic" : "") << ": " << hits.size()
                  << " site(s)";
        for (std::size_t h : hits) {
            std::cout << " at position " << h + 1; // counted from 1, as in a sequence viewer
        }
        std::cout << '\n';
    }
    return 0;
}
