import os


def part1(input):
    num_open_parentheses = input.count("(")
    num_closed_parentheses = input.count(")")
    return num_open_parentheses - num_closed_parentheses


def part2(input):
    current_floor = 0
    for i, char in enumerate(input):
        if char == "(":
            current_floor += 1
        elif char == ")":
            current_floor -= 1

        if current_floor < 0:
            return i + 1


if __name__ == "__main__":
    script_path = os.path.dirname(os.path.realpath(__file__))
    input = open(f"{script_path}/../data/01.txt", "r").read()
    print(f"Part 1: {part1(input)}")
    print(f"Part 2: {part2(input)}")
