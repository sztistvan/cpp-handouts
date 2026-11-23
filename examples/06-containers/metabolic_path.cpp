// Shortest reaction path in a (simplified) metabolic network: breadth-first search on a graph.
// The graph is a map: a metabolite -> the metabolites that one enzymatic step can turn it into.
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

using Graph = std::map<std::string, std::vector<std::string>>;

// Returns the path from `from` to `to`, or an empty vector if `to` cannot be reached.
std::vector<std::string> shortest_path(const Graph& graph, const std::string& from, const std::string& to)
{
    std::map<std::string, std::string> parent; // also tells which metabolites have been reached
    std::queue<std::string> frontier;
    parent[from] = from;
    frontier.push(from);
    while (!frontier.empty()) {
        const std::string current = frontier.front();
        frontier.pop();
        if (current == to) {
            break;
        }
        const auto found = graph.find(current);
        if (found == graph.end()) {
            continue; // no outgoing reaction known
        }
        for (const std::string& next : found->second) {
            if (parent.count(next) == 0) { // not reached yet
                parent[next] = current;
                frontier.push(next);
            }
        }
    }

    std::vector<std::string> path;
    if (parent.count(to) == 0) {
        return path;
    }
    for (std::string node = to; node != from; node = parent[node]) {
        path.push_back(node);
    }
    path.push_back(from);
    std::reverse(path.begin(), path.end());
    return path;
}

void show(const Graph& graph, const std::string& from, const std::string& to)
{
    const std::vector<std::string> path = shortest_path(graph, from, to);
    std::cout << from << " -> " << to << ": ";
    if (path.empty()) {
        std::cout << "no path in this network\n";
        return;
    }
    std::cout << path.size() - 1 << " steps: ";
    for (std::size_t i = 0; i < path.size(); ++i) {
        std::cout << (i == 0 ? "" : " > ") << path[i];
    }
    std::cout << '\n';
}

int main()
{
    // Glycolysis and two neighbors, strongly simplified: each arrow is one enzymatic step.
    const Graph graph = {
        {"Glc", {"G6P"}},
        {"G6P", {"F6P", "6PG"}}, // 6PG: the entrance to the pentose phosphate pathway
        {"F6P", {"FBP"}},
        {"FBP", {"DHAP", "GAP"}},
        {"DHAP", {"GAP"}},
        {"GAP", {"BPG13"}},
        {"BPG13", {"PG3"}},
        {"PG3", {"PG2"}},
        {"PG2", {"PEP"}},
        {"PEP", {"Pyr"}},
        {"Pyr", {"Lac", "AcCoA"}},
    };

    std::cout << "Metabolites with outgoing reactions: " << graph.size() << '\n';
    show(graph, "Glc", "Pyr");
    show(graph, "Glc", "Lac");
    show(graph, "DHAP", "Pyr");
    show(graph, "Pyr", "Glc");
    return 0;
}
