// Integer versus decimal division: the most common silent error in numerical code.
#include <iostream>

int main()
{
    // Colony counts on three plates.
    const int plate1 = 12;
    const int plate2 = 15;
    const int plate3 = 14;
    const int total = plate1 + plate2 + plate3;

    std::cout << "total / 3            = " << total / 3 << "   (integer division: decimals cut off)\n";
    std::cout << "total / 3.0          = " << total / 3.0 << "\n";
    std::cout << "double(total) / 3    = " << static_cast<double>(total) / 3 << "\n";

    // A fraction written with whole numbers.
    const int positive = 3;
    const int all = 4;
    std::cout << "3 / 4 * 100          = " << positive / all * 100 << "   (3 / 4 is 0 first!)\n";
    std::cout << "100.0 * 3 / 4        = " << 100.0 * positive / all << "\n";
    std::cout << "3 * 100 / 4          = " << positive * 100 / all << "   (integer, but happens to be exact)\n";
    return 0;
}
