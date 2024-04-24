#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Function to perform Depth-First Search
void DFS(const vector<vector<int>>& graph, int start) {
    int numNodes = graph.size();
    vector<bool> visited(numNodes, false); // Mark all nodes as not visited
    stack<int> s;

    // Mark the start node as visited and push it onto the stack
    visited[start] = true;
    s.push(start);

    // DFS traversal loop
    while (!s.empty()) {
        // Pop a node from the stack and process it
        int current = s.top();
        s.pop();
        cout << current << " ";

        // Push all unvisited neighbors of the current node onto the stack
        for (int neighbor : graph[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                s.push(neighbor);
            }
        }
    }
}

int main() {
    // Define the graph as a vector of vectors
    vector<vector<int>> graph = {
        {1, 2},     // Node 0 is connected to nodes 1 and 2
        {0, 3, 4},  // Node 1 is connected to nodes 0, 3, and 4
        {0, 5},     // Node 2 is connected to nodes 0 and 5
        {1},        // Node 3 is connected to node 1
        {1},        // Node 4 is connected to node 1
        {2}         // Node 5 is connected to node 2
    };

    // Perform DFS from node 0
    cout << "DFS Traversal: ";
    DFS(graph, 0);

    return 0;
}
