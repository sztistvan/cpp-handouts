// Dijkstra's algorithm on a terrain with different costs: the cheapest path is not the shortest one.
// Search thread, version 5 (continued): a priority queue always expands the cheapest cell first.
#include <algorithm>
#include <cstddef>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <utility>
#include <vector>

#ifndef DATA_DIR
#define DATA_DIR "data"
#endif

struct Cell {
    int row;
    int col;
};

// (cost so far, cell number = row * cols + col). A pair is compared by its first element first.
using Item = std::pair<int, int>;

// The cost of entering a cell: a digit 1-9 is its own cost, anything else that can be walked on costs 1.
int cell_cost(char c)
{
    if (c >= '1' && c <= '9') {
        return c - '0';
    }
    return 1;
}

bool same(const Cell& a, const Cell& b)
{
    return a.row == b.row && a.col == b.col;
}

bool load_grid(const std::string& path, std::vector<std::string>& grid)
{
    std::ifstream in(path);
    if (!in) {
        std::cerr << "Cannot open " << path << '\n';
        return false;
    }
    grid.clear();
    std::string line;
    while (std::getline(in, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (!line.empty()) {
            grid.push_back(line);
        }
    }
    return !grid.empty();
}

Cell find_cell(const std::vector<std::string>& grid, char target)
{
    for (std::size_t r = 0; r < grid.size(); ++r) {
        const std::size_t c = grid[r].find(target);
        if (c != std::string::npos) {
            return Cell{static_cast<int>(r), static_cast<int>(c)};
        }
    }
    return Cell{-1, -1};
}

const int step_row[4] = {-1, 1, 0, 0};
const int step_col[4] = {0, 0, -1, 1};

bool can_enter(const std::vector<std::string>& grid, int r, int c)
{
    return r >= 0 && r < static_cast<int>(grid.size()) && c >= 0 && c < static_cast<int>(grid[0].size()) &&
           grid[r][c] != '#';
}

// Breadth-first search: fewest steps. It does not look at the costs at all.
std::vector<std::vector<Cell>> bfs(const std::vector<std::string>& grid, Cell start)
{
    const int rows = static_cast<int>(grid.size());
    const int cols = static_cast<int>(grid[0].size());
    std::vector<std::vector<Cell>> parent(rows, std::vector<Cell>(cols, Cell{-1, -1}));
    std::vector<std::vector<bool>> seen(rows, std::vector<bool>(cols, false));
    std::queue<Cell> frontier;
    seen[start.row][start.col] = true;
    frontier.push(start);
    while (!frontier.empty()) {
        const Cell current = frontier.front();
        frontier.pop();
        for (int k = 0; k < 4; ++k) {
            const int r = current.row + step_row[k];
            const int c = current.col + step_col[k];
            if (can_enter(grid, r, c) && !seen[r][c]) {
                seen[r][c] = true;
                parent[r][c] = current;
                frontier.push(Cell{r, c});
            }
        }
    }
    return parent;
}

// Dijkstra's algorithm: the cheapest path. All costs must be positive.
std::vector<std::vector<Cell>> dijkstra(const std::vector<std::string>& grid, Cell start)
{
    const int rows = static_cast<int>(grid.size());
    const int cols = static_cast<int>(grid[0].size());
    const int unreached = std::numeric_limits<int>::max();
    std::vector<std::vector<int>> cost(rows, std::vector<int>(cols, unreached));
    std::vector<std::vector<Cell>> parent(rows, std::vector<Cell>(cols, Cell{-1, -1}));

    // std::greater turns the priority queue upside down: the SMALLEST cost comes out first.
    std::priority_queue<Item, std::vector<Item>, std::greater<Item>> frontier;
    cost[start.row][start.col] = 0;
    frontier.push(Item(0, start.row * cols + start.col));
    while (!frontier.empty()) {
        const Item top = frontier.top();
        frontier.pop();
        const int r0 = top.second / cols;
        const int c0 = top.second % cols;
        if (top.first > cost[r0][c0]) {
            continue; // an outdated entry: a cheaper way to this cell was found meanwhile
        }
        for (int k = 0; k < 4; ++k) {
            const int r = r0 + step_row[k];
            const int c = c0 + step_col[k];
            if (!can_enter(grid, r, c)) {
                continue;
            }
            const int new_cost = top.first + cell_cost(grid[r][c]);
            if (new_cost < cost[r][c]) {
                cost[r][c] = new_cost;
                parent[r][c] = Cell{r0, c0};
                frontier.push(Item(new_cost, r * cols + c));
            }
        }
    }
    return parent;
}

// The path from start to goal, following the parents backwards.
std::vector<Cell> path_to(const std::vector<std::vector<Cell>>& parent, Cell start, Cell goal)
{
    std::vector<Cell> path;
    Cell cell = goal;
    while (!same(cell, start)) {
        path.push_back(cell);
        cell = parent[cell.row][cell.col];
        if (cell.row < 0) {
            return std::vector<Cell>(); // no path
        }
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}

int path_cost(const std::vector<std::string>& grid, const std::vector<Cell>& path)
{
    int total = 0;
    for (std::size_t i = 1; i < path.size(); ++i) { // entering the start costs nothing
        total += cell_cost(grid[path[i].row][path[i].col]);
    }
    return total;
}

void report(const char* title, const std::vector<std::string>& grid, const std::vector<Cell>& path, char mark)
{
    std::cout << title << ": " << path.size() - 1 << " steps, cost " << path_cost(grid, path) << '\n';
    std::vector<std::string> shown = grid;
    for (std::size_t i = 1; i + 1 < path.size(); ++i) { // not the start and not the goal
        shown[path[i].row][path[i].col] = mark;
    }
    for (const std::string& row : shown) {
        std::cout << row << '\n';
    }
    std::cout << '\n';
}

int main()
{
    std::vector<std::string> grid;
    if (!load_grid(std::string(DATA_DIR) + "/terrain.txt", grid)) {
        return 1;
    }
    const Cell start = find_cell(grid, 'S');
    const Cell goal = find_cell(grid, 'G');

    std::cout << "terrain.txt: " << grid.size() << " rows, " << grid[0].size() << " columns\n";
    std::cout << "A digit is the cost of entering the cell, # is a wall.\n\n";

    report("Fewest steps (breadth-first search)", grid, path_to(bfs(grid, start), start, goal), '*');
    report("Cheapest path (Dijkstra)", grid, path_to(dijkstra(grid, start), start, goal), '+');
    return 0;
}
