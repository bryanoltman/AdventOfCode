import os


def surface_area(l, w, h):
    return 2 * l * w + 2 * w * h + 2 * h * l


def line_to_dimensions(line):
    return tuple(map(int, line.split("x")))


def part1(input):
    sum = 0
    for i in input:
        l, w, h = line_to_dimensions(i)
        area = surface_area(l, w, h)
        sum += area
    return area


def part2(input):
    pass


if __name__ == "main":
    script_path = os.path.dirname(os.path.realpath(__file__))
    input = open(f"{script_path}/input.txt", "r").read().splitlines()
    print(f"Part 1: {part1(input)}")
    print(f"Part 2: {part2(input)}")
