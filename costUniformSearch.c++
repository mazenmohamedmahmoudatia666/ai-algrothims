#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
#include <algorithm> // Include this header for the reverse function

using namespace std;

// Function to implement Uniform Cost Search
vector<char> uniform_cost_search(const unordered_map<char, unordered_map<char, int>>& graph, char start, char goal) {
    unordered_map<char, int> distances;
    unordered_map<char, char> parent;
    priority_queue<pair<int, char>, vector<pair<int, char>>, greater<pair<int, char>>> pq;

    // Initialize distances with infinity and start node with 0
    for (auto& node : graph) {
        distances[node.first] = INT_MAX;
    }
    distances[start] = 0;

    pq.push({0, start});

    while (!pq.empty()) {
        int cost = pq.top().first;
        char node = pq.top().second;
        pq.pop();

        if (node == goal) {
            // Reconstruct the path
            vector<char> path;
            while (node != start) {
                path.push_back(node);
                node = parent[node];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }

        for (auto& neighbor : graph.at(node)) {
            char next_node = neighbor.first;
            int weight = neighbor.second;

            if (distances[node] + weight < distances[next_node]) {
                distances[next_node] = distances[node] + weight;
                parent[next_node] = node;
                pq.push({distances[next_node], next_node});
            }
        }
    }

    return {}; // Return empty vector if no path found
}

int main() {
    unordered_map<char, unordered_map<char, int>> graph = {
        {'A', {{'B', 2}, {'C', 5}}},
        {'B', {{'D', 3}}},
        {'C', {{'D', 1}}},
        {'D', {{'E', 4}}},
        {'E', {}}
    };

    char start_node = 'A';
    char goal_node = 'E';

    vector<char> shortest_path = uniform_cost_search(graph, start_node, goal_node);

    if (!shortest_path.empty()) {
        cout << "Shortest path from " << start_node << " to " << goal_node << ": ";
        for (char node : shortest_path) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "No path found from " << start_node << " to " << goal_node << endl;
    }

    return 0;
}
