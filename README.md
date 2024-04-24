# Ai-algrothims
# TASK
- A*

. The provided code implements the A* algorithm for pathfinding in a 2D grid. Here's a summary of the algorithm:

Definitions:
The grid is represented as a 2D vector, where each element represents a cell in the grid. Values of 0 represent empty cells, and values of 1 represent walls.
A Node struct represents each cell in the grid. It contains coordinates (x, y), cost functions g and h, and a pointer to the parent node.
Heuristic Function:
The Manhattan distance heuristic is used to estimate the distance between a node and the goal node. It calculates the sum of absolute differences in the x and y coordinates.
Find Neighbors Function:
This function finds the neighboring cells of a given node in the grid. It checks the four adjacent cells (up, down, left, right) to ensure they are within the grid boundaries and not walls.
A Search Function*:
The A* algorithm is implemented using a priority queue (openList) to store nodes to be explored. Nodes are prioritized based on their total cost f() = g + h.
The algorithm starts from the start node and iteratively explores neighboring nodes until the goal node is reached or all reachable nodes are explored.
During exploration, each node's g value (the cost of reaching that node from the start node) and h value (the heuristic estimate of the remaining cost to reach the goal node) are updated.
Once the goal node is reached, the algorithm backtracks from the goal node to the start node, constructing the shortest path.
The path is then reversed and returned.
Main Function:
The main function initializes the example grid, start node, and goal node.
It calls the AStar function to find the shortest path from the start node to the goal node.
Finally, it prints the coordinates of the nodes along the shortest path and cleans up memory by deleting dynamically allocated nodes.
This implementation demonstrates how the A* algorithm can be used to find the shortest path in a 2D grid efficiently.

- DFs
- BFS
- Greedy 
- Cost uniform search
- MinMax
- Alpha beta 
