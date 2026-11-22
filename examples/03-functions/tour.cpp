// A quick tour of functions: parameters, return values, references, defaults, overloading.
#include <iostream>
#include <string>

// Declaration (prototype): tells the compiler that this function exists.
// The definition (the body) may come later in the file.
double mean(double a, double b);

// Definition of a function with a return value.
int add(int a, int b)
{
    return a + b;
}

// A function that returns nothing: its return type is void.
void print_label(const std::string& label, double value) // const reference: no copy, no change
{
    std::cout << label << " = " << value << '\n';
}

// By value: the function works on a COPY. The caller's variable is not changed.
void increment_copy(int n)
{
    ++n;
}

// By reference: the function works on the ORIGINAL variable.
void increment(int& n)
{
    ++n;
}

// Overloading: the same name, different parameters.
double mean(double a, double b, double c)
{
    return (a + b + c) / 3.0;
}

// Default argument: used when the caller leaves the last argument out.
double to_micro(double value, double factor = 1.0e6)
{
    return value * factor;
}

int main()
{
    std::cout << "add(2, 3) = " << add(2, 3) << '\n';

    int counter = 10;
    increment_copy(counter);
    std::cout << "after increment_copy: " << counter << '\n';
    increment(counter);
    std::cout << "after increment:      " << counter << '\n';

    print_label("mean of 4 and 7", mean(4.0, 7.0));
    print_label("mean of 4, 7 and 10", mean(4.0, 7.0, 10.0));

    print_label("0.25 mol/L in umol/L", to_micro(0.25));
    print_label("0.25 in thousands", to_micro(0.25, 1000.0));
    return 0;
}

// The definition of the function declared above main.
double mean(double a, double b)
{
    return (a + b) / 2.0;
}
