# Puzzle Game Solver

This repository contains a C++ implementation of a puzzle game solver, focusing on solving sliding tile puzzles using Breadth-First Search (BFS) and custom algorithms for optimized tile movement. The code supports generating random puzzle configurations and finding the shortest solution to return the puzzle to its solved state.

## Overview

The project includes the following key components:

- **Puzzle Representation:** The puzzle board is stored as a 2D vector, where each tile is represented by a number. The tile `0` represents the empty space, which can be moved to solve the puzzle.

- **BFS Solver:** A Breadth-First Search (BFS) is implemented to solve the final two rows of the puzzle in an efficient manner, ensuring that the solution is optimal.

- **Puzzle Logic:** The game handles random puzzle generation, user interactions, and the step-by-step solving of the puzzle. It includes methods to determine valid moves, move tiles, and check if the puzzle is solved.

## Classes and Functionality

### 1. `Storage` (Base Class)
Holds the structure of the puzzle table and solution configuration. It includes:
- `table`: 2D vector storing the current state of the puzzle.
- `solution`: 2D vector storing the final solved state.
- `zero`: Coordinates of the empty space.
- `size`: Size of the puzzle.

### 2. `BFS`
Used to solve the puzzle with the BFS algorithm. Key components:
- **State:** Represents the current state of the board and path of moves.
- **Hashing and Equality:** Custom hash and equality functions for unordered maps.
- **SolvePuzzle:** Finds the solution for the last two rows of the puzzle efficiently.

### 3. `General_function`
Derived from `Storage`, this class includes:
- **Puzzle Manipulation:** Methods to move tiles, check proximity to the empty space, and find tile positions.
- **Randomization:** Generates random puzzle configurations by shuffling the board.
- **Print & Check:** Prints the puzzle board and checks if it's solved.

### 4. `Puzzle_game`
Extends `General_function` and provides the full solving mechanism:
- **Move Logic:** Contains helper methods to move the empty space in various directions (up, down, left, right).
- **Solving Strategy:** Optimizes the movement of tiles to their correct positions and calls BFS to solve the last two rows.
- **Main Solve Function:** Combines the logic to solve the puzzle iteratively and efficiently.

## How It Works

1. **Setup Puzzle:** The user can input the size of the puzzle (e.g., 3x3, 4x4) and the program generates a random puzzle configuration.
2. **Solve the Puzzle:** The `solve()` function generates a sequence of moves to solve the puzzle.
3. **Interactive Display:** After each move, the puzzle is printed to the console to show the current state, along with the tile that was moved.

## Limitations

For puzzles larger than 5x5, the algorithm may become slower due to the increased number of states to explore.

# API Documentation

## Puzzle_game Class

This class provides the main interface for solving sliding tile puzzles. It inherits from `General_function` and adds higher-level puzzle-solving logic, using BFS for efficiency in solving the last two rows.

### Public Methods:

### 1. `void set_size(unsigned int n)`
- **Description:** Initializes the puzzle with a grid size `n x n` and sets the board in a solved state.
- **Parameters:**
    - `n (unsigned int)`: The size of the puzzle.
- **Usage Example:**
  ```cpp
  Puzzle_game puzzle;
  puzzle.set_size(3);  // Initializes a 3x3 puzzle.
  ```

### 2. `pair<int, int> find(int value)`
- **Description:** Locates the coordinates of a specific tile value on the board.
- **Parameters:**
    - `value (int)`: The value of the tile to find.
- **Returns:** A `pair<int, int>` containing the row and column of the tile.
- **Usage Example:**
  ```cpp
  pair<int, int> cords = puzzle.find(5);  // Finds the position of tile 5.
  ```

### 3. `bool move(int value)`
- **Description:** Moves the tile with the given value to the empty space, if adjacent to it.
- **Parameters:**
    - `value (int)`: The value of the tile to move.
- **Returns:** A `bool` indicating whether the move was successful.
- **Usage Example:**
  ```cpp
  if (puzzle.move(4)) {
      // Successfully moved tile 4
  }
  ```

### 4. `void make_random()`
- **Description:** Randomizes the puzzle by making multiple valid moves to shuffle the tiles. Ensures that the puzzle remains solvable.
- **Usage Example:**
  ```cpp
  puzzle.make_random();  // Randomizes the puzzle.
  ```

### 5. `vector<vector<int> > get_table()`
- **Description:** Returns the current state of the puzzle board.
- **Returns:** A 2D vector representing the current puzzle.
- **Usage Example:**
  ```cpp
  vector<vector<int>> board = puzzle.get_table();  // Gets the current board state.
  ```

### 6. `bool is_solved()`
- **Description:** Checks if the current puzzle state matches the solved configuration.
- **Returns:** A `bool` indicating whether the puzzle is solved.
- **Usage Example:**
  ```cpp
  if (puzzle.is_solved()) {
      cout << "Puzzle is solved!" << endl;
  }
  ```

### 7. `void test_print()`
- **Description:** Prints the current puzzle board to the console in a formatted manner.
- **Usage Example:**
  ```cpp
  puzzle.test_print();  // Prints the current puzzle state.
  ```

### 8. `vector<int> solve()`
- **Description:** Solves the entire puzzle, returning a sequence of moves required to solve it.
- **Returns:** A `vector<int>` representing the sequence of tile values moved during the solving process.
- **Usage Example:**
  ```cpp
  vector<int> solution = puzzle.solve();  // Solves the puzzle and returns the move sequence.
  for (int move : solution) {
      cout << "Move: " << move << endl;
  }
  ```

## BFS Class

This class provides the BFS algorithm for efficiently solving the last two rows of the puzzle.

### Public Methods:

### 1. `BFS(int r, int c)`
- **Description:** Constructor to initialize the BFS solver for a puzzle of size `r x c`.
- **Parameters:**
    - `r (int)`: The number of rows in the puzzle.
    - `c (int)`: The number of columns in the puzzle.
- **Usage Example:**
  ```cpp
  BFS solver(2, 4);  // Initializes BFS for solving a 2x4 puzzle section.
  ```

### 2. `vector<int> solvePuzzle(const vector<vector<int>> &board)`
- **Description:** Solves the given puzzle section using BFS.
- **Parameters:**
    - `board (const vector<vector<int>>& board)`: The puzzle section to solve (typically the last two rows).
- **Returns:** A `vector<int>` representing the sequence of moves required to solve the section.
- **Usage Example:**
  ```cpp
  vector<int> solution = solver.solvePuzzle(lastTwoRows);
  ```

## Use example

1. **Initialize the puzzle:**
   ```cpp
   Puzzle_game puzzle;
   puzzle.set_size(4);  // Set up a 4x4 puzzle.
   puzzle.make_random();  // Shuffle the puzzle.
   ```

2. **Solve the puzzle:**
   ```cpp
   vector<int> solution = puzzle.solve();  // Get the sequence of moves to solve the puzzle.
   ```

3. **Print the moves:**
   ```cpp
   for (int move : solution) {
       cout << "Move: " << move << endl;
   }
   ```

## License

This project is open-source and available under the MIT License.