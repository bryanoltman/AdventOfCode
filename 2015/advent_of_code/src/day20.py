from collections import defaultdict
from itertools import combinations
import math
import os


def divisors(n):
    large_divisors = []
    for i in range(1, int(math.sqrt(n) + 1)):
        if n % i == 0:
            yield i
            if i * i != n:
                large_divisors.append(n / i)
    for divisor in reversed(large_divisors):
        yield divisor


def num_presents_for_house(house_num):
    ret = 0
    for i in divisors(house_num):
        ret += i
    return int(ret * 10)


def part1(input):
    min_score = int(input)
    # Pick a high enough starting point given the input
    current_house = 100000
    while True:
        presents = num_presents_for_house(current_house)
        if presents >= min_score:
            return current_house
        current_house += 1


def part2(input):
    return 0


if __name__ == "__main__":
    script_path = os.path.dirname(os.path.realpath(__file__))
    input = open(f"{script_path}/../data/20.txt", "r").read().strip()
    print(f"Part 1: {part1(input)}")
    print(f"Part 2: {part2(input)}")
