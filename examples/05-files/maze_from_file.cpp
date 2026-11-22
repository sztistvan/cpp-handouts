// Reading the maze from a text file, with checks. Search thread, version 4.
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#ifndef DATA_DIR
#define DATA_DIR "data"
#endif

// Reads the maze at `path` into `maze`. On failure it returns false and puts a message into `message`.
bool load_maze(const std::string& path, std::vector<std::string>& maze, std::string& message)
{
    std::ifstream in(path);
    if (!in) {
        message = "cannot open the file";
        return false;
    }

    maze.clear();
    std::string line;
    while (std::getline(in, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (line.empty()) {
            continue;
        }
        if (!maze.empty() && line.size() != maze[0].size()) {
            message = "row " + std::to_string(maze.size() + 1) + " has " + std::to_string(line.size()) +
                      " characters, expected " + std::to_string(maze[0].size());
            return false;
        }
        maze.push_back(line);
    }
    if (maze.empty()) {
        message = "the file is empty";
        return false;
    }

    int starts = 0;
    int goals = 0;
    for (const std::string& row : maze) {
        for (char cell : row) {
            if (cell == 'S') {
                ++starts;
            }
            if (cell == 'G') {
                ++goals;
            }
        }
    }
    if (starts != 1 || goals != 1) {
        message = "the maze needs exactly one S and one G";
        return false;
    }
    return true;
}

int main()
{
    std::vector<std::string> maze;
    std::string message;

    if (load_maze(std::string(DATA_DIR) + "/maze.txt", maze, message)) {
        std::size_t start_row = 0, start_col = 0, goal_row = 0, goal_col = 0;
        int walls = 0;
        for (std::size_t r = 0; r < maze.size(); ++r) {
            std::cout << maze[r] << '\n';
            if (maze[r].find('S') != std::string::npos) {
                start_row = r;
                start_col = maze[r].find('S');
            }
            if (maze[r].find('G') != std::string::npos) {
                goal_row = r;
                goal_col = maze[r].find('G');
            }
            for (char cell : maze[r]) {
                if (cell == '#') {
                    ++walls;
                }
            }
        }
        std::cout << "\nmaze.txt: " << maze.size() << " rows, " << maze[0].size() << " columns, " << walls << " walls\n";
        std::cout << "start (" << start_row << ", " << start_col << "), goal (" << goal_row << ", " << goal_col << ")\n";
    } else {
        std::cout << "maze.txt: " << message << '\n';
    }

    // A file that does not exist: the program reports it instead of crashing.
    if (!load_maze(std::string(DATA_DIR) + "/maze_missing.txt", maze, message)) {
        std::cout << "maze_missing.txt: " << message << '\n';
    }
    return 0;
}
