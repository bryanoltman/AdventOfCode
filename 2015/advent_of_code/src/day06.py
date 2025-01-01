from enum import Enum
import os
import re

from advent_of_code.util.ranges import inclusive_range


class Operation(Enum):
    TOGGLE = 1
    TURN_ON = 2
    TURN_OFF = 3


class Instruction:
    def __init__(self, operation, x_range, y_range):
        self.operation = operation
        self.x_range = x_range
        self.y_range = y_range

    def __str__(self):
        return f"{self.operation} {self.x_range} {self.y_range}"

    def parse_from_line(line: str):
        turn_on_regex = re.compile(r"turn on (\d+),(\d+) through (\d+),(\d+)")
        turn_off_regex = re.compile(r"turn off (\d+),(\d+) through (\d+),(\d+)")
        toggle_regex = re.compile(r"toggle (\d+),(\d+) through (\d+),(\d+)")
        op = None

        if turn_on_regex.match(line):
            op = Operation.TURN_ON
            m = turn_on_regex.match(line)
        elif turn_off_regex.match(line):
            op = Operation.TURN_OFF
            m = turn_off_regex.match(line)
        elif toggle_regex.match(line):
            op = Operation.TOGGLE
            m = toggle_regex.match(line)

        if not op:
            raise Exception("no op found")

        x_range = inclusive_range(int(m.group(1)), int(m.group(3)))
        y_range = inclusive_range(int(m.group(2)), int(m.group(4)))
        return Instruction(op, x_range, y_range)


def count_grid(grid) -> int:
    return sum([sum(row) for row in grid])


def part1(input):
    lines = filter(len, input.splitlines())
    instructions = [Instruction.parse_from_line(l.strip()) for l in lines]
    grid = [[0] * 1000 for _ in range(1000)]
    for i in instructions:
        for y in i.y_range:
            for x in i.x_range:
                if i.operation is Operation.TOGGLE:
                    grid[y][x] = 0 if grid[y][x] else 1
                elif i.operation is Operation.TURN_ON:
                    grid[y][x] = 1
                else:
                    grid[y][x] = 0

    return count_grid(grid)


def part2(input):
    lines = filter(len, input.splitlines())
    instructions = [Instruction.parse_from_line(l.strip()) for l in lines]
    grid = [[0] * 1000 for _ in range(1000)]
    for i in instructions:
        for y in i.y_range:
            for x in i.x_range:
                if i.operation is Operation.TOGGLE:
                    grid[y][x] = grid[y][x] + 2
                elif i.operation is Operation.TURN_ON:
                    grid[y][x] = grid[y][x] + 1
                else:
                    grid[y][x] = max(0, grid[y][x] - 1)

    return count_grid(grid)


if __name__ == "__main__":
    script_path = os.path.dirname(os.path.realpath(__file__))
    input = open(f"{script_path}/../data/06.txt", "r").read().strip()
    print(f"Part 1: {part1(input)}")
    print(f"Part 2: {part2(input)}")
