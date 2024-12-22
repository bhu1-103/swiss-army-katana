import os
import random
from collections import deque

def generate_maze(size):
    maze = [[0 for _ in range(size)] for _ in range(size)]

    def is_valid(x, y):
        if x <= 0 or y <= 0 or x >= size - 1 or y >= size - 1:
            return False
        count = 0
        for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            nx, ny = x + dx, y + dy
            if 0 <= nx < size and 0 <= ny < size and maze[nx][ny] == 1:
                count += 1
        return count <= 1  

    def carve(x, y):
        maze[x][y] = 1
        directions = [(0, -1), (-1, 0), (0, 1), (1, 0)]
        random.shuffle(directions)
        for dx, dy in directions:
            nx, ny = x + dx, y + dy
            if is_valid(nx, ny):
                carve(nx, ny)

    carve(random.randint(1, size - 2), random.randint(1, size - 2))

    maze[1][0] = 1
    maze[size - 2][size - 1] = 1

    return maze

def is_solvable(maze, size):
    start, end = (1, 0), (size - 2, size - 1)
    queue = deque([start])
    visited = set()
    visited.add(start)

    while queue:
        x, y = queue.popleft()
        if (x, y) == end:
            return True

        for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            nx, ny = x + dx, y + dy
            if 0 <= nx < size and 0 <= ny < size and maze[nx][ny] == 1 and (nx, ny) not in visited:
                queue.append((nx, ny))
                visited.add((nx, ny))

    return False

def save_maze(maze, folder, count):
    os.makedirs(folder, exist_ok=True)
    filepath = os.path.join(folder, f"maze_{count}.txt")
    with open(filepath, "w") as f:
        for row in maze:
            f.write("".join("##" if cell == 0 else "  " for cell in row) + "\n")

def generate_and_save_mazes(size, max_iterations=100):
    solvable_count = 0
    not_solvable_count = 0

    for i in range(max_iterations):
        maze = generate_maze(size)
        if is_solvable(maze, size):
            solvable_count += 1
            save_maze(maze, "./solvable", solvable_count)
        else:
            not_solvable_count += 1
            save_maze(maze, "./not-solvable", not_solvable_count)

if __name__ == "__main__":
    maze_size = 16
    max_iterations = 1000
    generate_and_save_mazes(maze_size, max_iterations)
