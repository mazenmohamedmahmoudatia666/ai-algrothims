#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <unordered_map>

using namespace std;

// Function to implement Dijkstra's algorithm
void dijkstra(vector<unordered_map<int, int>>& graph, int start, vector<int>& distances) {
    int num_nodes = graph.size();
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Initialize distances array
    distances.assign(num_nodes, INT_MAX);
    distances[start] = 0;

    pq.push({0, start});

    while (!pq.empty()) {
        int dist = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if (dist > distances[node]) continue;

        for (auto& neighbor : graph[node]) {
            int next_node = neighbor.first;
            int weight = neighbor.second;

            if (dist + weight < distances[next_node]) {
                distances[next_node] = dist + weight;
                pq.push({distances[next_node], next_node});
            }
        }
    }
}

int main() {
    int num_nodes = 4;
    vector<unordered_map<int, int>> graph(num_nodes);

    // Example graph represented as an adjacency list
    graph[0] = {{1, 2}, {2, 4}};
    graph[1] = {{2, 1}, {3, 7}};
    graph[2] = {{3, 3}};
    graph[3] = {{1, 1}};

    int start_node = 0;
    vector<int> distances;

    dijkstra(graph, start_node, distances);

    cout << "Shortest distances from node " << start_node << ":" << endl;
    for (int i = 0; i < num_nodes; ++i) {
        cout << "Node: " << i << " Distance: ";
        if (distances[i] == INT_MAX) {
            cout << "Infinity" << endl;
        } else {
            cout << distances[i] << endl;
        }
    }

    return 0;
}
