// Translating a coding DNA sequence into a protein with the standard genetic code (a map codon -> amino acid),
// and counting the codons.
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

// The standard genetic code as 64 letters. The codons are ordered by their bases in the order T, C, A, G:
// TTT, TTC, TTA, TTG, TCT, ... GGG. '*' is a stop codon.
std::map<std::string, char> make_genetic_code()
{
    const std::string amino_acids = "FFLLSSSSYY**CC*WLLLLPPPPHHQQRRRRIIIMTTTTNNKKSSRRVVVVAAAADDEEGGGG";
    const std::string bases = "TCAG";
    std::map<std::string, char> code;
    std::size_t index = 0;
    for (char first : bases) {
        for (char second : bases) {
            for (char third : bases) {
                code[std::string{first, second, third}] = amino_acids[index];
                ++index;
            }
        }
    }
    return code;
}

int main()
{
    const std::map<std::string, char> code = make_genetic_code();
    const std::string dna = "ATGGCCATTGTAATGGGCCGCTGAAAGGGTGCCCGATAG";

    std::string protein;
    std::map<std::string, int> usage;
    for (std::size_t i = 0; i + 3 <= dna.size(); i += 3) {
        const std::string codon = dna.substr(i, 3);
        protein.push_back(code.at(codon)); // at() stops with an error for a codon that is not in the map
        ++usage[codon];
    }

    std::cout << "genetic code: " << code.size() << " codons\n";
    std::cout << "DNA:     " << dna << " (" << dna.size() << " bases)\n";
    std::cout << "protein: " << protein << " (* = stop)\n\n";

    std::cout << "codons used more than once:\n";
    for (const auto& entry : usage) {
        if (entry.second > 1) {
            std::cout << "  " << entry.first << " (" << code.at(entry.first) << ") x" << entry.second << '\n';
        }
    }
    std::cout << "ATG -> " << code.at("ATG") << ", TGG -> " << code.at("TGG") << ", TAA -> " << code.at("TAA") << '\n';
    return 0;
}
