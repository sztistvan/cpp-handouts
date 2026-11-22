// A maze as a vector of strings, and a table of distances as a vector of vectors.
// Search thread, version 3: the data structure that breadth-first search will use in handout 6.
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    // # = wall, . = free, S = start, G = goal
    const std::vector<std::string> maze = {
        "###########",
        "#S..#.....#",
        "#.#.#.###.#",
        "#.#...#...#",
        "#.#####.#G#",
        "#.......#.#",
        "###########",
    };
    const std::size_t rows = maze.size();
    const std::size_t cols = maze[0].size();

    // Find S and G, and count the cells.
    std::size_t start_row = 0, start_col = 0, goal_row = 0, goal_col = 0;
    int walls = 0;
    int free_cells = 0;
    for (std::size_t r = 0; r < rows; ++r) {
        const std::size_t s = maze[r].find('S'); // npos if there is no S in this row
        if (s != std::string::npos) {
            start_row = r;
            start_col = s;
        }
        const std::size_t g = maze[r].find('G');
        if (g != std::string::npos) {
            goal_row = r;
            goal_col = g;
        }
        for (char cell : maze[r]) {
            if (cell == '#') {
                ++walls;
            } else {
                ++free_cells;
            }
        }
    }

    std::cout << "Maze: " << rows << " rows, " << cols << " columns\n";
    std::cout << "Start at (" << start_row << ", " << start_col << "), goal at (" << goal_row << ", " << goal_col << ")\n";
    std::cout << "Walls: " << walls << ", free cells (including S and G): " << free_cells << "\n\n";

    // A table with the same shape as the maze. -1 means "not reached yet".
    std::vector<std::vector<int>> distance(rows, std::vector<int>(cols, -1));
    distance[start_row][start_col] = 0;

    std::cout << "Distance table (### wall, . not reached yet, number = steps from the start):\n";
    for (std::size_t r = 0; r < rows; ++r) {
        for (std::size_t c = 0; c < cols; ++c) {
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
