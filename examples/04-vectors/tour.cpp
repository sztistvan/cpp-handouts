// A quick tour of std::vector and std::string.
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int main()
{
    // --- vector: a row of values that can grow ---
    std::vector<double> temperatures = {36.6, 37.1, 38.4};
    temperatures.push_back(36.9); // append at the end
    std::cout << "size: " << temperatures.size() << ", first: " << temperatures[0]
              << ", last: " << temperatures.back() << '\n';

    std::vector<int> zeros(5, 0); // five elements, all 0
    std::cout << "zeros has " << zeros.size() << " elements\n";

    // Range-for: visit every element (each element is copied into t).
    double sum = 0.0;
    for (double t : temperatures) {
        sum += t;
    }
    std::cout << "sum = " << sum << '\n';

    // Range-for with a reference: t IS the element, so changing t changes the vector.
    for (double& t : temperatures) {
        t -= 36.6; // difference to a normal temperature
    }
    std::cout << "differences:";
    for (double t : temperatures) {
        std::cout << ' ' << t;
    }
    std::cout << '\n';

    // [] does not check the index, at() does.
    try {
        std::cout << temperatures.at(10) << '\n';
    } catch (const std::out_of_range& error) {
        std::cout << "at(10) failed: " << error.what() << '\n';
    }

    // size() is an UNSIGNED number: subtracting from 0 wraps around.
    std::vector<int> empty;
    std::cout << "empty.size() - 1 = " << empty.size() - 1 << '\n';

    // A vector of vectors: a table with 3 rows and 4 columns, filled with 0.
    std::vector<std::vector<int>> table(3, std::vector<int>(4, 0));
    table[1][2] = 7; // row 1, column 2
    for (const std::vector<int>& row : table) {
        for (int value : row) {
            std::cout << value << ' ';
        }
        std::cout << '\n';
    }

    // --- string: a row of characters ---
    std::string seq = "ATGGCC";
    seq += "TAA"; // append text
    std::cout << "\nseq = " << seq << ", length " << seq.length() << ", first character " << seq[0] << '\n';
    std::cout << "first codon: " << seq.substr(0, 3) << '\n';
    std::cout << "GCC starts at position " << seq.find("GCC") << '\n';
    if (seq.find("XYZ") == std::string::npos) {
        std::cout << "XYZ not found\n";
    }
    std::cout << "seq == \"ATGGCCTAA\": " << (seq == "ATGGCCTAA") << '\n';
    return 0;
}
