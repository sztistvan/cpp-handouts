// Breadth-first search (BFS) in the maze: the shortest path, counted in steps.
// Search thread, version 5: a queue explores the maze in rings of growing distance from the start.
#include <cstddef>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#ifndef DATA_DIR
#define DATA_DIR "data"
#endif

struct Cell {
    int row;
    int col;
};

// Reads the maze (as in handout 5). Returns false and a message if something is wrong.
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
            message = "rows have different lengths";
            return false;
        }
        maze.push_back(line);
    }
    if (maze.empty()) {
        message = "the file is empty";
        return false;
    }
    return true;
}

Cell find_cell(const std::vector<std::string>& maze, char target)
{
    for (std::size_t r = 0; r < maze.size(); ++r) {
        const std::size_t c = maze[r].find(target);
        if (c != std::string::npos) {
            return Cell{static_cast<int>(r), static_cast<int>(c)};
        }
    }
    return Cell{-1, -1};
}

int main()
{
    std::vector<std::string> maze;
    std::string message;
    if (!load_maze(std::string(DATA_DIR) + "/maze.txt", maze, message)) {
        std::cerr << "maze.txt: " << message << '\n';
        return 1;
    }
    const int rows = static_cast<int>(maze.size());
    const int cols = static_cast<int>(maze[0].size());
    const Cell start = find_cell(maze, 'S');
    const Cell goal = find_cell(maze, 'G');

    // distance[r][c] = steps from the start, -1 = not reached yet. parent[r][c] = the cell we came from.
    std::vector<std::vector<int>> distance(rows, std::vector<int>(cols, -1));
    std::vector<std::vector<Cell>> parent(rows, std::vector<Cell>(cols, Cell{-1, -1}));

    const int step_row[4] = {-1, 1, 0, 0}; // up, down, left, right
    const int step_col[4] = {0, 0, -1, 1};

    std::queue<Cell> frontier; // cells that are reached, but whose neighbors are not looked at yet
    distance[start.row][start.col] = 0;
    frontier.push(start);
    while (!frontier.empty()) {
        const Cell current = frontier.front();
        frontier.pop();
        for (int k = 0; k < 4; ++k) {
            const int r = current.row + step_row[k];
            const int c = current.col + step_col[k];
            const bool inside = r >= 0 && r < rows && c >= 0 && c < cols;
            if (inside && maze[r][c] != '#' && distance[r][c] == -1) {
                distance[r][c] = distance[current.row][current.col] + 1;
                parent[r][c] = current;
                frontier.push(Cell{r, c});
            }
        }
    }

    int reached = 0;
    for (const std::vector<int>& row : distance) {
        for (int d : row) {
            if (d >= 0) {
                ++reached;
            }
        }
    }

    std::cout << "Cells reached from S: " << reached << '\n';
    if (distance[goal.row][goal.col] < 0) {
        std::cout << "G cannot be reached from S\n";
        return 0;
    }
    std::cout << "Shortest path from S to G: " << distance[goal.row][goal.col] << " steps\n\n";

    // Walk back from G to S through the parents, and mark the path with '*'.
    std::vector<std::string> shown = maze;
    Cell cell = parent[goal.row][goal.col];
    while (cell.row != start.row || cell.col != start.col) {
        shown[cell.row][cell.col] = '*';
        cell = parent[cell.row][cell.col];
    }
    std::cout << "Path:\n";
    for (const std::string& row : shown) {
        std::cout << row << '\n';
    }

    std::cout << "\nDistance table (### wall, number = steps from S, . = not reached):\n";
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (maze[r][c] == '#') {
                std::cout << "###";
            } else if (distance[r][c] < 0) {
                std::cout << "  .";
            } else {
                std::cout << std::setw(3) << distance[r][c];
            }
        }
        std::cout << '\n';
    }
    return 0;
}
