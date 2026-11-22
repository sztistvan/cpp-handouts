// Reading a log file: split each line into date, time, level and message, and count the levels.
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#ifndef DATA_DIR
#define DATA_DIR "data"
#endif

int main()
{
    const std::string path = std::string(DATA_DIR) + "/run.log";
    std::ifstream in(path);
    if (!in) {
        std::cerr << "Cannot open " << path << '\n';
        return 1;
    }

    int infos = 0;
    int warnings = 0;
    int errors = 0;

    std::string line;
    while (std::getline(in, line)) {
        std::istringstream stream(line);
        std::string date;
        std::string time;
        std::string level;
        stream >> date >> time >> level; // >> reads one word at a time
        std::string message;
        std::getline(stream, message);   // the rest of the line (it starts with a space)
        if (!message.empty() && message[0] == ' ') {
            message.erase(0, 1);
        }

        if (level == "INFO") {
            ++infos;
        } else if (level == "WARNING") {
            ++warnings;
            std::cout << time << "  WARNING  " << message << '\n';
        } else if (level == "ERROR") {
            ++errors;
            std::cout << time << "  ERROR    " << message << '\n';
        }
    }

    std::cout << "\nINFO: " << infos << ", WARNING: " << warnings << ", ERROR: " << errors << '\n';
    return 0;
}
