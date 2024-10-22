# GD1P02-2024-S2-Assignment2

# Dungeon Map Pathfinding

This project is a C++ implementation of a dungeon map pathfinding algorithm. It loads a 20x20 dungeon map, validates the map, and allows users to perform Depth-First Search (DFS), Breadth-First Search (BFS), and A* pathfinding on the map. The program outputs the dungeon map with the path marked, and uses colored text for start, end, and path markers.

## Features

- **Map Loading**: Loads a 20x20 dungeon map from a text file.
- **Map Validation**: Ensures the map has exactly one start (`s`), one end (`x`), and 10 items (`a-j`).
- **Pathfinding Algorithms**:
  - **DFS (Depth-First Search)**: Displays the order in which items can be collected.
  - **BFS (Breadth-First Search)**: Displays the order in which items can be collected.
  - **A* Pathfinding**: Finds the optimal path from the start (`s`) to the end (`x`), marking the path on the map.
- **Colored Output**: Uses ANSI escape codes to display colored markers in the terminal:
  - Start point (`s`) is shown in **green**.
  - End point (`x`) is shown in **red**.
  - Path points (`p`) are shown in **yellow**.
  
  ## Libraries Used

This project only relies on the C++ Standard Library, no external libraries are required. Key headers used include:
- `<iostream>`: For console input and output operations.
- `<fstream>`: For file reading.
- `<vector>`: For dynamic arrays to store the dungeon map.
- `<queue>`: Used for the BFS algorithm.
- `<stack>`: Used for the DFS algorithm.
- `<cmath>`: For mathematical operations (like distance calculations).
- `<set>` and `<map>`: To manage visited nodes and tracking paths in A*.


## Map Format

The map must be a 20x20 grid stored in a `.txt` file, where:
- `w` represents a wall (obstacle).
- `.` represents a clear square that can be traversed.
- `s` represents the start point.
- `x` represents the end point.
- `a-j` represent collectible items.

### Example Map (`map1.txt`)

```plaintext
wwwwwwwwwwwwwwwwwwww
ws.......a.........w
w.....b..w..cw.....w
w............w.....w
w.d..........w.....w
w............w.....w
w.....ww.e...w.....w
w.....w.....f......w
w.....w............w
wwwwwwwwwwg........w
w..................w
w..................w
w............h.....w
wwwwwwww...........w
w..................w
w....i........wwwwww
w..................x
w............j.....w
w..................w
wwwwwwwwwwwwwwwwwwww
```

## Requirements

- A C++ compiler that supports at least C++11.
- A terminal that supports ANSI escape codes (for colored output). Use PowerShell, Windows Terminal, or any UNIX-like terminal (Linux/Mac).



## How to Use

1. Place your 20x20 map file in the project directory (e.g., `map1.txt`).
2. When prompted, enter the filename of the map you want to load:
    ```bash
    Enter the map filename (e.g., map1.txt): map1.txt
    ```

3. After the map is loaded, choose one of the operations:
   - **1**: Run DFS to collect items.
   - **2**: Run BFS to collect items.
   - **3**: Run A* to find the optimal path from start to end.
   - **4**: Reload the map.
   - **5**: Exit the program.

### Sample Run

```
Enter the map filename (e.g., map1.txt): map1.txt
wwwwwwwwwwwwwwwwwwww
ws.......a.........w
w.....b..w..cw.....w
w............w.....w
w.d..........w.....w
w............w.....w
w.....ww.e...w.....w
w.....w.....f......w
w.....w............w
wwwwwwwwwwg........w
w..................w
w..................w
w............h.....w
wwwwwwww...........w
w..................w
w....i........wwwwww
w..................x
w............j.....w
w..................w
wwwwwwwwwwwwwwwwwwww

Choose an operation:
1. DFS Collection Order
2. BFS Collection Order
3. A* Pathfinding
4. Reload Map
5. Exit
```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
