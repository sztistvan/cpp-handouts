// Swapping two values: by value does nothing useful, by reference works.
#include <iostream>
#include <utility>

void swap_by_value(int a, int b) // a and b are copies
{
    const int temp = a;
    a = b;
    b = temp;
}

void swap_by_reference(int& a, int& b) // a and b ARE the caller's variables
{
    const int temp = a;
    a = b;
    b = temp;
}

int main()
{
    int x = 3;
    int y = 8;
    std::cout << "start:              x = " << x << ", y = " << y << '\n';

    swap_by_value(x, y);
    std::cout << "swap_by_value:      x = " << x << ", y = " << y << "  (nothing happened)\n";

    swap_by_reference(x, y);
    std::cout << "swap_by_reference:  x = " << x << ", y = " << y << '\n';

    std::swap(x, y); // the standard library already provides this
    std::cout << "std::swap:          x = " << x << ", y = " << y << '\n';
    return 0;
}
