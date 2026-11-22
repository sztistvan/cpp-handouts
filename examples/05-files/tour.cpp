// A quick tour of files: writing, reading line by line, splitting a line, converting text to numbers.
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// DATA_DIR and OUTPUT_DIR are set by CMake. If you compile by hand, run the program from the repository root.
#ifndef DATA_DIR
#define DATA_DIR "data"
#endif
#ifndef OUTPUT_DIR
#define OUTPUT_DIR "."
#endif

// Cut a line into fields at every delimiter.
std::vector<std::string> split(const std::string& line, char delimiter)
{
    std::vector<std::string> fields;
    std::istringstream stream(line); // a string that can be read like a file
    std::string field;
    while (std::getline(stream, field, delimiter)) {
        fields.push_back(field);
    }
    return fields;
}

// Convert text to a number. Returns false if the text is not a number, or if anything is left over.
bool parse_double(const std::string& text, double& value)
{
    std::istringstream stream(text);
    stream >> value;
    if (stream.fail()) {
        return false;
    }
    stream >> std::ws; // skip white space after the number
    return stream.eof(); // true only if the whole text was used
}

int main()
{
    const std::string demo_path = std::string(OUTPUT_DIR) + "/demo.txt";

    // --- Writing: an std::ofstream is used exactly like std::cout ---
    {
        std::ofstream out(demo_path);
        if (!out) {
            std::cerr << "Cannot write demo.txt\n";
            return 1;
        }
        out << "sample,value\n";
        out << "A,1.5\n";
        out << "B,2.25\n";
    } // the file is closed here, when `out` goes out of scope

    // --- Reading line by line ---
    std::ifstream in(demo_path);
    if (!in) {
        std::cerr << "Cannot read demo.txt\n";
        return 1;
    }
    std::string line;
    int number = 0;
    while (std::getline(in, line)) { // false at the end of the file
        ++number;
        std::cout << "line " << number << ": " << line << '\n';
    }

    // --- A file that does not exist ---
    std::ifstream missing(std::string(DATA_DIR) + "/no_such_file.txt");
    if (!missing) {
        std::cout << "no_such_file.txt: cannot open\n";
    }

    // --- Splitting a line ---
    std::cout << '\n';
    const std::vector<std::string> examples = {"S01,control,98.2", "a,,c", "a,b,"};
    for (const std::string& text : examples) {
        const std::vector<std::string> fields = split(text, ',');
        std::cout << '"' << text << "\" -> " << fields.size() << " fields:";
        for (const std::string& f : fields) {
            std::cout << " [" << f << ']';
        }
        std::cout << '\n';
    }

    // --- Converting text to numbers ---
    std::cout << '\n';
    const std::vector<std::string> texts = {"98.2", "1e3", "  7 ", "12abc", "98,2", ""};
    for (const std::string& text : texts) {
        double value = 0.0;
        std::cout << '"' << text << "\" -> ";
        if (parse_double(text, value)) {
            std::cout << value << '\n';
        } else {
            std::cout << "rejected\n";
        }
    }
    return 0;
}
