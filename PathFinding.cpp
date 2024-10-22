#include "PathFinding.h"
#include <queue>
#include <stack>
#include <iostream>
#include <cmath>
#include <set>
#include <map>
#include <tuple>
#include <vector>
#include <algorithm>

// Euclidean distance (not used in A*)
double euclideanDistance(int x1, int y1, int x2, int y2) {
    return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

// Manhattan distance (used in A*)
double manhattanDistance(int x1, int y1, int x2, int y2) {
    return std::abs(x2 - x1) + std::abs(y2 - y1);
}

// Depth-First Search (DFS) with boundary checking
void DFS(const Map& map) {
    std::stack<std::pair<int, int>> stack;
    std::set<std::pair<int, int>> visited;
    stack.push(map.getStart());

    std::cout << "DFS Collection Order: ";
    std::vector<char> collectedItems;

    while (!stack.empty()) {
        // Get the top element from the stack and extract coordinates
        std::pair<int, int> current = stack.top();
        int x = current.first;
        int y = current.second;
        stack.pop();

        if (visited.count({ x, y }) == 0) {
            visited.insert({ x, y });
            char cell = map.getCell(x, y);
            if (cell >= 'a' && cell <= 'j') {
                collectedItems.push_back(cell);
            }

            // Push neighbors (right, down, left, up) with boundary checking
            std::vector<std::pair<int, int>> neighbors = { {x + 1, y}, {x, y + 1}, {x - 1, y}, {x, y - 1} };
            for (const auto& neighbor : neighbors) {
                int nx = neighbor.first;
                int ny = neighbor.second;
                // Ensure the neighbor is within bounds of the map
                if (nx >= 0 && nx < map.grid[0].size() && ny >= 0 && ny < map.grid.size()) {
                    if (map.getCell(nx, ny) != 'w') {
                        stack.push({ nx, ny });
                    }
                }
            }
        }
    }

    // Print the collected items in order
    for (char item : collectedItems) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

// Breadth-First Search (BFS) with boundary checking
void BFS(const Map& map) {
    std::queue<std::pair<int, int>> queue;
    std::set<std::pair<int, int>> visited;
    queue.push(map.getStart());

    std::cout << "BFS Collection Order: ";
    std::vector<char> collectedItems;

    while (!queue.empty()) {
        // Get the front element from the queue and extract coordinates
        std::pair<int, int> current = queue.front();
        int x = current.first;
        int y = current.second;
        queue.pop();

        if (visited.count({ x, y }) == 0) {
            visited.insert({ x, y });
            char cell = map.getCell(x, y);
            if (cell >= 'a' && cell <= 'j') {
                collectedItems.push_back(cell);
            }

            // Push neighbors (up, right, down, left) with boundary checking
            std::vector<std::pair<int, int>> neighbors = { {x, y - 1}, {x + 1, y}, {x, y + 1}, {x - 1, y} };
            for (const auto& neighbor : neighbors) {
                int nx = neighbor.first;
                int ny = neighbor.second;
                // Ensure the neighbor is within bounds of the map
                if (nx >= 0 && nx < map.grid[0].size() && ny >= 0 && ny < map.grid.size()) {
                    if (map.getCell(nx, ny) != 'w') {
                        queue.push({ nx, ny });
                    }
                }
            }
        }
    }

    // Print the collected items in order
    for (char item : collectedItems) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

// A* Algorithm with boundary checking
void AStar(Map& map) {
    auto start = map.getStart();
    auto end = map.getEnd();

    std::priority_queue<std::tuple<double, int, int>, std::vector<std::tuple<double, int, int>>, std::greater<>> openList;
    std::set<std::pair<int, int>> closedList;
    std::map<std::pair<int, int>, std::pair<int, int>> cameFrom;

    openList.emplace(0.0, start.first, start.second);
    std::map<std::pair<int, int>, double> gScore;
    gScore[{start.first, start.second}] = 0.0;

    while (!openList.empty()) {
        // Get the top element from the priority queue and extract coordinates
        std::tuple<double, int, int> currentTuple = openList.top();
        double currentF = std::get<0>(currentTuple);
        int currentX = std::get<1>(currentTuple);
        int currentY = std::get<2>(currentTuple);
        openList.pop();

        // If we reached the goal, reconstruct the path
        if (std::make_pair(currentX, currentY) == end) {
            std::cout << "A* Path Found!" << std::endl;

            // Reconstruct the path from end to start
            std::vector<std::pair<int, int>> path;
            auto current = std::make_pair(currentX, currentY);
            while (cameFrom.find(current) != cameFrom.end()) {
                path.push_back(current);
                current = cameFrom[current];
            }
            path.push_back(start);

            // Mark the path on the map
            for (const auto& coord : path) {
                int x = coord.first;
                int y = coord.second;
                if (map.getCell(x, y) != 's' && map.getCell(x, y) != 'x') {
                    map.grid[y][x] = 'p';
                }
            }

            map.displayMap();
            return;
        }

        closedList.insert({ currentX, currentY });

        // Check neighbors (up, right, down, left) with boundary checking
        std::vector<std::pair<int, int>> neighbors = {
            {currentX, currentY - 1}, {currentX + 1, currentY},
            {currentX, currentY + 1}, {currentX - 1, currentY}
        };

        for (const auto& neighbor : neighbors) {
            int nx = neighbor.first;
            int ny = neighbor.second;
            // Ensure the neighbor is within bounds of the map
            if (nx >= 0 && nx < map.grid[0].size() && ny >= 0 && ny < map.grid.size()) {
                if (map.getCell(nx, ny) == 'w' || closedList.count({ nx, ny })) continue;

                double tentativeG = gScore[{currentX, currentY}] + 1.0;

                if (gScore.find({ nx, ny }) == gScore.end() || tentativeG < gScore[{nx, ny}]) {
                    gScore[{nx, ny}] = tentativeG;
                    double fScore = tentativeG + manhattanDistance(nx, ny, end.first, end.second);
                    openList.emplace(fScore, nx, ny);
                    cameFrom[{nx, ny}] = { currentX, currentY };
                }
            }
        }
    }

    std::cout << "No path found using A*." << std::endl;
}
