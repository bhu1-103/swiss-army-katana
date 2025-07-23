# Maze Generator and Solver

This Python script generates random, solvable mazes and saves them as text files.

## How It Works

1.  **Generation:** The `generate_maze` function uses a recursive backtracking algorithm. It starts at a random point and carves a path through the grid, ensuring that it doesn't create loops or enclosed walls.

2.  **Validation:** After a maze is generated, the `is_solvable` function runs a Breadth-First Search (BFS) algorithm to find a path from the designated start point to the end point. This guarantees that every maze saved is valid and has a solution.

3.  **Output:** The script will generate two folders, `solvable` and `not-solvable`, and place the generated mazes in the appropriate folder. The mazes are saved as `.txt` files, where `##` represents a wall and a space represents a path.