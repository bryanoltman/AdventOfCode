import re
import os


def chars_in_str(string):
    if string.startswith('"') and string.endswith('"'):
        string = string[1 : len(string) - 1]
    string = string.replace(r"\"", '"')
    string = string.replace(r"\\", ".")
    string = re.sub(r"\\x..", "x", string)
    return len(string)


def encoded_str_len(string):
    base_len = len(string)
    chars = [ord(c) for c in string]
    num_backslashes = sum(1 for c in chars if c == ord("\\"))
    num_quotes = sum(1 for c in chars if c == ord('"'))
    return base_len + num_backslashes + num_quotes + 2


def part1(input):
    sum = 0
    for line in input.strip().split("\n"):
        sum += len(line) - chars_in_str(line)
    return sum


def part2(input):
    sum = 0
    for line in input.strip().split("\n"):
        sum += encoded_str_len(line) - len(line)
    return sum


if __name__ == "__main__":
    script_path = os.path.dirname(os.path.realpath(__file__))
    input = open(f"{script_path}/../data/08.txt", "r").read().strip()
    print(f"Part 1: {part1(input)}")
    print(f"Part 2: {part2(input)}")
