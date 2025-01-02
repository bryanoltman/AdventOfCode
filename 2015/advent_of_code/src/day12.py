import json
import os


def count_json_part_1(obj) -> int:
    total = 0
    if type(obj) is list:
        total += sum(count_json_part_1(o) for o in obj)
    elif type(obj) is dict:
        total += sum(count_json_part_1(v) for v in obj.values())
    elif type(obj) is int:
        total += obj

    return total


def part1(input):
    return count_json_part_1(json.loads(input))


def count_json_part_2(obj) -> int:
    total = 0
    if type(obj) is list:
        total += sum(count_json_part_2(o) for o in obj)
    elif type(obj) is dict:
        if "red" in obj.values():
            return total
        total += sum(count_json_part_2(v) for v in obj.values())
    elif type(obj) is int:
        total += obj

    return total


def part2(input):
    return count_json_part_2(json.loads(input))


if __name__ == "__main__":
    script_path = os.path.dirname(os.path.realpath(__file__))
    input = open(f"{script_path}/../data/12.txt", "r").read().strip()
    print(f"Part 1: {part1(input)}")
    print(f"Part 2: {part2(input)}")
