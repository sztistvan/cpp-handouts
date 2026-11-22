// Reading the parameters of a simulation from a text file ("key = value" lines).
// Simulation thread, version 5: change the parameters without recompiling the program.
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#ifndef DATA_DIR
#define DATA_DIR "data"
#endif

bool parse_double(const std::string& text, double& value)
{
    std::istringstream stream(text);
    stream >> value;
    if (stream.fail()) {
        return false;
    }
    stream >> std::ws;
    return stream.eof();
}

// Remove spaces and tabs at both ends.
std::string trim(const std::string& text)
{
    const std::string white = " \t\r";
    const std::size_t first = text.find_first_not_of(white);
    if (first == std::string::npos) {
        return ""; // only white space
    }
    const std::size_t last = text.find_last_not_of(white);
    return text.substr(first, last - first + 1);
}

double logistic_step(double population, double r, double capacity)
{
    return population + r * population * (1.0 - population / capacity);
}

int main()
{
    // Default values, used for anything the file does not mention.
    double r = 0.1;
    double capacity = 100.0;
    double start = 1.0;
    int generations = 10;

    const std::string path = std::string(DATA_DIR) + "/parameters.txt";
    std::ifstream in(path);
    if (!in) {
        std::cerr << "Cannot open " << path << '\n';
        return 1;
    }

    std::string line;
    int line_number = 0;
    while (std::getline(in, line)) {
        ++line_number;
        line = trim(line);
        if (line.empty() || line[0] == '#') {
            continue; // empty line or comment
        }
        const std::size_t equals = line.find('=');
        if (equals == std::string::npos) {
            std::cout << "line " << line_number << ": no '=' found, ignored\n";
            continue;
        }
        const std::string key = trim(line.substr(0, equals));
        const std::string text = trim(line.substr(equals + 1));

        double value = 0.0;
        if (!parse_double(text, value)) {
            std::cout << "line " << line_number << ": '" << text << "' is not a number, ignored\n";
            continue;
        }

        if (key == "r") {
            r = value;
        } else if (key == "capacity") {
            capacity = value;
        } else if (key == "start") {
            start = value;
        } else if (key == "generations") {
            generations = static_cast<int>(value);
        } else {
            std::cout << "line " << line_number << ": unknown parameter '" << key << "', ignored\n";
        }
    }

    std::cout << "Parameters used:\n";
    std::cout << "  r = " << r << "\n  capacity = " << capacity << "\n  start = " << start
              << "\n  generations = " << generations << '\n';

    double population = start;
    for (int t = 0; t < generations; ++t) {
        population = logistic_step(population, r, capacity);
    }
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "Population after " << generations << " generations: " << population << '\n';
    return 0;
}
