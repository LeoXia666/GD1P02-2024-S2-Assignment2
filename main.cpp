#include <iostream>
#include "Map.h"
#include "PathFinding.h"

int main() {
    Map map;
    std::string filename;

    std::cout << "Enter the map filename: ";
    std::cin >> filename;

    if (!map.loadMap(filename)) {
        std::cerr << "Failed to load or verify the map." << std::endl;
        return 1;
    }

    map.displayMap();

    bool running = true;
    while (running) {
        int option;
        std::cout << "\nChoose an operation:\n1. DFS Collection Order\n2. BFS Collection Order\n3. A* Pathfinding\n4. Reload Map\n5. Exit\n";
        std::cin >> option;

        switch (option) {
        case 1:
            DFS(map);
            break;
        case 2:
            BFS(map);
            break;
        case 3:
            AStar(map);
            break;
        case 4:
            std::cout << "Enter the map filename: ";
            std::cin >> filename;
            if (!map.loadMap(filename)) {
                std::cerr << "Failed to load or verify the map." << std::endl;
                return 1;
            }
            map.displayMap();
            break;
        case 5:
            running = false;
            break;
        default:
            std::cout << "Invalid option!" << std::endl;
        }
    }

    return 0;
}
