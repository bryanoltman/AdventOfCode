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
        area += min(l * w, w * h, h * l)
        sum += area
    return sum


def smallest_perimeter(l, w, h):
    return min(2 * l + 2 * w, 2 * w + 2 * h, 2 * h + 2 * l)


def volume(l, w, h):
    return l * w * h


def part2(input):
    sum = 0
    for i in input:
        l, w, h = line_to_dimensions(i)
        perimeter = smallest_perimeter(l, w, h)
        vol = volume(l, w, h)
        sum += perimeter + vol

    return sum


if __name__ == "__main__":
    script_path = os.path.dirname(os.path.realpath(__file__))
    input = open(f"{script_path}/../data/02.txt", "r").read().splitlines()
    print(f"Part 1: {part1(input)}")
    print(f"Part 2: {part2(input)}")
