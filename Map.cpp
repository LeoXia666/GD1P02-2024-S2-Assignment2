#include "Map.h"
#include <fstream>
#include <iostream>

bool Map::loadMap(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return false;
    }

    grid.clear();
    items.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (line.size() == 20) {
            grid.push_back(line);
        }
    }

    return validateMap();
}

void Map::displayMap() const {
    for (const auto& row : grid) {
        for (const char& cell : row) {
            // Check the character and apply corresponding color
            if (cell == 's') {
                // Green for start
                std::cout << "\033[32m" << cell << "\033[0m";  // Green
            }
            else if (cell == 'x') {
                // Red for end
                std::cout << "\033[31m" << cell << "\033[0m";  // Red
            }
            else if (cell == 'p') {
                // Yellow for path
                std::cout << "\033[33m" << cell << "\033[0m";  // Yellow
            }
            else if (cell == 'w') {
                // Keep walls white or default color
                std::cout << cell;
            }
            else {
                // Default color for other cells
                std::cout << cell;
            }
        }
        std::cout << std::endl;
    }
}


bool Map::validateMap() {
    int startCount = 0;
    int endCount = 0;
    int itemCount = 0;

    // Check if the map has exactly 20 rows and each row has 20 columns
    if (grid.size() != 20) {
        std::cerr << "Invalid map: The map must have exactly 20 rows." << std::endl;
        return false;
    }
    for (const auto& row : grid) {
        if (row.size() != 20) {
            std::cerr << "Invalid map: Each row must have exactly 20 columns." << std::endl;
            return false;
        }
    }

    // Loop through the grid to check for start, end, and item counts
    for (int y = 0; y < grid.size(); ++y) {
        for (int x = 0; x < grid[y].size(); ++x) {
            char cell = grid[y][x];
            if (cell == 's') {
                start = { x, y };
                startCount++;
            }
            else if (cell == 'x') {
                end = { x, y };
                endCount++;
            }
            else if (cell >= 'a' && cell <= 'j') {
                items.push_back({ x, y });
                itemCount++;
            }
        }
    }

    // Ensure there is exactly one start and one end point
    if (startCount != 1) {
        std::cerr << "Invalid map: There must be exactly one start point ('s')." << std::endl;
        return false;
    }
    if (endCount != 1) {
        std::cerr << "Invalid map: There must be exactly one end point ('x')." << std::endl;
        return false;
    }

    // Ensure there are exactly 10 items
    if (itemCount != 10) {
        std::cerr << "Invalid map: There must be exactly 10 items ('a' to 'j')." << std::endl;
        return false;
    }

    return true;
}

char Map::getCell(int x, int y) const {
    return grid[y][x];
}

std::pair<int, int> Map::getStart() const {
    return start;
}

std::pair<int, int> Map::getEnd() const {
    return end;
}

std::vector<std::pair<int, int>> Map::getItems() const {
    return items;
}
