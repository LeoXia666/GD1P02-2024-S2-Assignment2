#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <utility>

class Map {
public:
    bool loadMap(const std::string& filename);
    void displayMap() const;
    bool isValid() const;

    char getCell(int x, int y) const;
    std::pair<int, int> getStart() const;
    std::pair<int, int> getEnd() const;
    std::vector<std::pair<int, int>> getItems() const;

    std::vector<std::string> grid; // 将 grid 设为公共的，以便在 AStar 中修改

private:
    std::pair<int, int> start;
    std::pair<int, int> end;
    std::vector<std::pair<int, int>> items;

    bool validateMap();
};

#endif // MAP_H
