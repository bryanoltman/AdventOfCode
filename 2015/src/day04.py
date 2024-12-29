import hashlib
import os


def part1(input):
    i = 1
    while True:
        md5 = hashlib.md5()
        string = f"{input}{i}"
        md5.update(string.encode("utf-8"))
        if md5.hexdigest().startswith("00000"):
            return i
        i += 1


def part2(input):
    i = 1
    while True:
        md5 = hashlib.md5()
        string = f"{input}{i}"
        md5.update(string.encode("utf-8"))
        if md5.hexdigest().startswith("000000"):
            return i
        i += 1


if __name__ == "__main__":
    script_path = os.path.dirname(os.path.realpath(__file__))
    input = open(f"{script_path}/../data/04.txt", "r").read().strip()
    print(f"Part 1: {part1(input)}")
    print(f"Part 2: {part2(input)}")
