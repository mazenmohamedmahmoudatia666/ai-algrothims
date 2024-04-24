#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Structure to represent a node in the graph
struct Node {
    int value;
    vector<Node*> neighbors;
    bool visited;

    Node(int val) : value(val), visited(false) {}
};

// Function to perform Breadth-First Search
void BFS(Node* start) {
    // Queue for BFS traversal
    queue<Node*> q;

    // Mark the start node as visited and enqueue it
    start->visited = true;
    q.push(start);

    // BFS traversal loop
    while (!q.empty()) {
        // Dequeue a node from the queue and process it
        Node* current = q.front();
        q.pop();
        cout << current->value << " ";

        // Enqueue all unvisited neighbors of the current node
        for (Node* neighbor : current->neighbors) {
            if (!neighbor->visited) {
                neighbor->visited = true;
                q.push(neighbor);
            }
        }
    }
}

int main() {
    // Create nodes
    Node* node1 = new Node(1);
    Node* node2 = new Node(2);
    Node* node3 = new Node(3);
    Node* node4 = new Node(4);
    Node* node5 = new Node(5);

    // Define graph connections
    node1->neighbors.push_back(node2);
    node1->neighbors.push_back(node3);
    node2->neighbors.push_back(node4);
    node3->neighbors.push_back(node4);
    node3->neighbors.push_back(node5);
    node4->neighbors.push_back(node5);

    // Perform BFS from node1
    cout << "BFS Traversal: ";
    BFS(node1);

    // Clean up memory
    delete node1;
    delete node2;
    delete node3;
    delete node4;
    delete node5;

    return 0;
}
