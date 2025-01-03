from itertools import chain
import os


def parse_input(input):
    return [l for l in input.split("\n") if l]


def neighbors(grid, x, y):
    possible_points = [
        (x - 1, y - 1),
        (x, y - 1),
        (x + 1, y - 1),
        (x - 1, y),
        (x + 1, y),
        (x - 1, y + 1),
        (x, y + 1),
        (x + 1, y + 1),
    ]
    width = len(grid[0])
    height = len(grid)
    neighbor_points = [
        p for p in possible_points if p[0] in range(width) and p[1] in range(height)
    ]
    return [grid[p[1]][p[0]] for p in neighbor_points]


def advance_step(grid):
    new_grid = []
    for y in range(len(grid)):
        line = ""
        for x in range(len(grid[0])):
            is_on = grid[y][x] == "#"
            num_on_neighbors = len([n for n in neighbors(grid, x, y) if n == "#"])
            if not is_on and num_on_neighbors == 3:
                line += "#"
            elif is_on and (num_on_neighbors == 2 or num_on_neighbors == 3):
                line += "#"
            else:
                line += "."
        new_grid.append(line)

    return new_grid


def part1(input):
    grid = parse_input(input)
    for _ in range(100):
        grid = advance_step(grid)

    flat_list = list(chain.from_iterable(grid))
    return sum(x == "#" for x in flat_list)


def part2(input):
    grid = parse_input(input)
    # Replace corners with "on" lights
    grid[0] = "#" + grid[0][1:-1] + "#"
    grid[-1] = "#" + grid[-1][1:-1] + "#"

    for _ in range(100):
        grid = advance_step(grid)
        grid[0] = "#" + grid[0][1:-1] + "#"
        grid[-1] = "#" + grid[-1][1:-1] + "#"

    flat_list = list(chain.from_iterable(grid))
    return sum(x == "#" for x in flat_list)


if __name__ == "__main__":
    script_path = os.path.dirname(os.path.realpath(__file__))
    input = open(f"{script_path}/../data/18.txt", "r").read().strip()
    print(f"Part 1: {part1(input)}")
    print(f"Part 2: {part2(input)}")
