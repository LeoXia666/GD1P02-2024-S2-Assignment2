#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "Map.h"

void DFS(const Map& map);
void BFS(const Map& map);
void AStar(Map& map);

#endif // PATHFINDING_H
