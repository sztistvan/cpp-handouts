// Reading input: a name and two numbers.
#include <iostream>
#include <string>

int main()
{
    std::cout << "What is your name? ";
    std::string name;
    std::getline(std::cin, name);
    std::cout << "Hello, " << name << "!\n";

    std::cout << "Enter two numbers: ";
    double a = 0.0;
    double b = 0.0;
    if (!(std::cin >> a >> b)) {
        std::cerr << "That was not a number.\n";
        return 1; // a non-zero return value tells the system that something went wrong
    }
    std::cout << a << " + " << b << " = " << a + b << '\n';
    return 0;
}
