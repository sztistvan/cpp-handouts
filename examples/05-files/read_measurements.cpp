// Reading a CSV file with messy real-world values, and summarising it by group.
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#ifndef DATA_DIR
#define DATA_DIR "data"
#endif

std::vector<std::string> split(const std::string& line, char delimiter)
{
    std::vector<std::string> fields;
    std::istringstream stream(line);
    std::string field;
    while (std::getline(stream, field, delimiter)) {
        fields.push_back(field);
    }
    return fields;
}

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

double mean(const std::vector<double>& values)
{
    double sum = 0.0;
    for (double v : values) {
        sum += v;
    }
    return sum / static_cast<double>(values.size());
}

double standard_deviation(const std::vector<double>& values)
{
    const double m = mean(values);
    double sum_of_squares = 0.0;
    for (double v : values) {
        sum_of_squares += (v - m) * (v - m);
    }
    return std::sqrt(sum_of_squares / static_cast<double>(values.size() - 1));
}

void print_group(const std::string& name, const std::vector<double>& values)
{
    std::cout << std::left << std::setw(9) << name + ":" << std::right << "n = " << values.size();
    if (values.size() >= 2) {
        std::cout << "   mean = " << mean(values) << "   SD = " << standard_deviation(values);
    } else {
        std::cout << "   (too few values)";
    }
    std::cout << '\n';
}

int main()
{
    const std::string path = std::string(DATA_DIR) + "/measurements.csv";
    std::ifstream in(path);
    if (!in) {
        std::cerr << "Cannot open " << path << '\n';
        return 1;
    }

    std::vector<double> control;
    std::vector<double> treated;
    int data_lines = 0;
    int skipped = 0;

    std::string line;
    int line_number = 0;
    while (std::getline(in, line)) {
        ++line_number;
        if (!line.empty() && line.back() == '\r') {
            line.pop_back(); // a file written on Windows may end its lines with \r\n
        }
        if (line_number == 1 || line.empty()) {
            continue; // header line, empty lines
        }
        ++data_lines;

        const std::vector<std::string> fields = split(line, ',');
        double rate = 0.0;
        // Exactly 3 fields are expected. (A decimal comma, as in "99,4", would create a fourth field.)
        if (fields.size() != 3 || !parse_double(fields[2], rate)) {
            std::cout << "line " << line_number << " skipped: " << line << '\n';
            ++skipped;
            continue;
        }

        if (fields[1] == "control") {
            control.push_back(rate);
        } else if (fields[1] == "treated") {
            treated.push_back(rate);
        } else {
            std::cout << "line " << line_number << " skipped (unknown group): " << line << '\n';
            ++skipped;
        }
    }

    std::cout << "\nData lines: " << data_lines << ", usable: " << data_lines - skipped << ", skipped: " << skipped
              << "\n\n";
    std::cout << std::fixed << std::setprecision(2);
    print_group("control", control);
    print_group("treated", treated);
    return 0;
}
