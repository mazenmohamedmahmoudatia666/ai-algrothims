#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm> // Include for reverse function

using namespace std;

// Structure to represent a node in the grid
struct Node {
    int x, y;           // Coordinates
    int g, h;           // Cost functions
    Node* parent;       // Parent node

    Node(int _x, int _y) : x(_x), y(_y), g(0), h(0), parent(nullptr) {}
    
    Node(const Node& other) : x(other.x), y(other.y), g(other.g), h(other.h), parent(other.parent) {}
    
    // Function to calculate the total cost f
    int f() const {
        return g + h;
    }
};

// Function to calculate the Manhattan distance heuristic
int heuristic(const Node& current, const Node& goal) {
    return abs(current.x - goal.x) + abs(current.y - goal.y);
}

// Function to find neighbors of a node in the grid
vector<Node*> findNeighbors(const Node& current, const vector<vector<int>>& grid) {
    vector<Node*> neighbors;
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    for (int i = 0; i < 4; ++i) {
        int newX = current.x + dx[i];
        int newY = current.y + dy[i];

        // Check if the neighbor is within the grid and not a wall
        if (newX >= 0 && newX < grid.size() && newY >= 0 && newY < grid[0].size() && grid[newX][newY] == 0) {
            neighbors.push_back(new Node(newX, newY));
        }
    }

    return neighbors;
}

// Function to perform A* search
vector<Node*> AStar(const vector<vector<int>>& grid, const Node& startNode, const Node& goalNode) {
    vector<Node*> path;
    priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> openList;
    vector<vector<bool>> closedList(grid.size(), vector<bool>(grid[0].size(), false));
    
    // Create copies of start and goal nodes
    Node start(startNode);
    Node goal(goalNode);

    // Set up the start node
    start.g = 0;
    start.h = heuristic(start, goal);
    openList.push({start.f(), new Node(start)});

    while (!openList.empty()) {
        Node* current = openList.top().second;
        openList.pop();

        // Goal check
        if (current->x == goal.x && current->y == goal.y) {
            Node* temp = current;
            while (temp != nullptr) {
                path.push_back(temp);
                temp = temp->parent;
            }
            reverse(path.begin(), path.end());
            break;
        }

        // Move current node from open to closed list
        closedList[current->x][current->y] = true;

        // Expand neighbors
        vector<Node*> neighbors = findNeighbors(*current, grid);
        for (Node* neighbor : neighbors) {
            if (closedList[neighbor->x][neighbor->y]) {
                continue;
            }

            // Calculate tentative g value
            int tentative_g = current->g + 1;

            if (tentative_g < neighbor->g || !closedList[neighbor->x][neighbor->y]) {
                neighbor->parent = current;
                neighbor->g = tentative_g;
                neighbor->h = heuristic(*neighbor, goal);

                // Add neighbor to the open list if not already present
                openList.push({neighbor->f(), neighbor});
            }
        }
    }

    // Clean up memory
    while (!openList.empty()) {
        delete openList.top().second;
        openList.pop();
    }

    return path;
}

int main() {
    // Example grid (0 represents empty space, 1 represents walls)
    vector<vector<int>> grid = {
        {0, 0, 0, 1, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1},
        {0, 0, 0, 0, 0}
    };

    Node start(0, 0);
    Node goal(4, 4);

    vector<Node*> path = AStar(grid, start, goal);

    // Print the path
    for (Node* node : path) {
        cout << "(" << node->x << ", " << node->y << ")" << endl;
    }

    // Clean up memory
    for (Node* node : path) {
        delete node;
    }

    return 0;
}
