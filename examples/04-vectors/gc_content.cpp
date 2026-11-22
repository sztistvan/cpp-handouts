// GC content of a DNA sequence: the fraction of G and C among the known bases.
// The sequence is invented for this example. It contains two unknown bases (N).
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <string>

int count_base(const std::string& dna, char base)
{
    int count = 0;
    for (char c : dna) {
        if (c == base) {
            ++count;
        }
    }
    return count;
}

// Fraction of G or C among the bases A, C, G and T (other characters, such as N, are ignored).
double gc_content(const std::string& dna)
{
    const int a = count_base(dna, 'A');
    const int c = count_base(dna, 'C');
    const int g = count_base(dna, 'G');
    const int t = count_base(dna, 'T');
    const int known = a + c + g + t;
    if (known == 0) {
        return 0.0;
    }
    return static_cast<double>(g + c) / known;
}

int main()
{
    const std::string dna = "ATGGCGTACGCTAGCTAGGCTTAACGGCTAGCNNATCGATCGGCTAAGCTTAGC";

    std::cout << "Sequence length: " << dna.length() << '\n';
    for (char base : std::string("ACGTN")) {
        std::cout << "  " << base << ": " << std::setw(2) << count_base(dna, base) << '\n';
    }
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "GC content: " << 100.0 * gc_content(dna) << " %\n";
    return 0;
}
