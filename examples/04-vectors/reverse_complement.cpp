// Reverse complement of a DNA sequence: swap A<->T and C<->G, and read the result backwards.
#include <cstddef>
#include <iostream>
#include <string>

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
    return 'N'; // anything else: unknown
}

std::string reverse_complement(const std::string& dna)
{
    std::string result;
    // Counting down with an unsigned index: i runs from size to 1, and we use dna[i - 1].
    for (std::size_t i = dna.size(); i > 0; --i) {
        result.push_back(complement(dna[i - 1]));
    }
    return result;
}

int main()
{
    const std::string dna = "ATGCGTAACG";
    std::cout << "sequence:           5'-" << dna << "-3'\n";
    std::cout << "reverse complement: 5'-" << reverse_complement(dna) << "-3'\n";

    const std::string site = "GAATTC"; // the recognition site of the enzyme EcoRI
    std::cout << "\n" << site << " -> " << reverse_complement(site)
              << (reverse_complement(site) == site ? "  (palindromic: reads the same on both strands)" : "") << '\n';
    return 0;
}
