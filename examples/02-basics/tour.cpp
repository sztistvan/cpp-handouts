// A quick tour of C++ basics: types, variables, operators, if/else, loops.
#include <iostream>
#include <string>

int main()
{
    // --- Types and variables ---
    int count = 12;              // whole numbers
    double concentration = 0.25; // decimal numbers (mol/L)
    bool is_ready = true;        // true or false
    char base = 'A';             // a single character
    std::string gene = "BRCA1";  // text

    std::cout << "count=" << count << " concentration=" << concentration
              << " is_ready=" << is_ready << " base=" << base << " gene=" << gene << '\n';

    // --- Operators ---
    int a = 7;
    int b = 2;
    std::cout << "7 / 2   = " << a / b << '\n';   // integer division: 3
    std::cout << "7 % 2   = " << a % b << '\n';   // remainder: 1
    std::cout << "7 / 2.0 = " << a / 2.0 << '\n'; // one decimal operand: 3.5

    count += 3; // same as: count = count + 3;
    ++count;    // same as: count = count + 1;
    std::cout << "count after += 3 and ++: " << count << '\n';

    // --- if / else ---
    double ph = 6.4;
    if (ph < 7.0) {
        std::cout << "pH " << ph << ": acidic\n";
    } else if (ph > 7.0) {
        std::cout << "pH " << ph << ": basic\n";
    } else {
        std::cout << "pH " << ph << ": neutral\n";
    }

    if (ph > 6.0 && ph < 8.0) { // && means "and", || means "or", ! means "not"
        std::cout << "within the physiological window\n";
    }

    // --- Loops ---
    int sum = 0;
    for (int i = 1; i <= 5; ++i) { // counting loop
        sum += i;
    }
    std::cout << "1+2+3+4+5 = " << sum << '\n';

    int n = 100;
    int halvings = 0;
    while (n > 1) { // loop while a condition holds
        n /= 2;
        ++halvings;
    }
    std::cout << "100 can be halved " << halvings << " times before reaching 1\n";

    for (int i = 1; i <= 10; ++i) {
        if (i % 2 == 0) {
            continue; // skip even numbers
        }
        if (i > 7) {
            break; // leave the loop completely
        }
        std::cout << "odd: " << i << '\n';
    }
    return 0;
}
