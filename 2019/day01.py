import os


def part1(input):
    sum = 0
    for line in input.splitlines():
        sum += (int(line) // 3) - 2
    return sum


def part2(input):
    sum = 0
    for line in input.splitlines():
        current_fuel = (int(line) // 3) - 2
        while current_fuel > 0:
            sum += current_fuel
            current_fuel = (int(current_fuel) // 3) - 2

    return sum


if __name__ == "__main__":
    script_path = os.path.dirname(os.path.realpath(__file__))
    input = open(f"{script_path}/data/01.txt", "r").read()
    print(f"Part 1: {part1(input)}")
    print(f"Part 2: {part2(input)}")
