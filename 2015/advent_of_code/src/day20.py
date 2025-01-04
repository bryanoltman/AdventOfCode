from collections import defaultdict
from itertools import combinations
import math
import os


# Reversed for part 2
def reversed_divisors(n):
    ret = []
    large_divisors = []
    for i in range(1, int(math.sqrt(n) + 1)):
        if n % i == 0:
            ret.append(i)
            if i * i != n:
                large_divisors.append(n / i)
    for divisor in large_divisors:
        ret.append(divisor)
    ret.sort(reverse=True)
    return ret


def num_presents_for_house(house_num):
    ret = 0
    for i in reversed_divisors(house_num):
        ret += i
    return int(ret * 10)


def part1(input):
    min_score = int(input)
    current_house = 1
    while True:
        presents = num_presents_for_house(current_house)
        if presents >= min_score:
            return current_house
        current_house += 1


def num_presents_for_house_part2(house_num):
    return sum(d * 11 for d in reversed_divisors(house_num)[:50])


def part2(input):
    min_score = int(input)
    current_house = 1
    while True:
        presents = num_presents_for_house_part2(current_house)
        if presents >= min_score:
            return current_house
        current_house += 1


if __name__ == "__main__":
    script_path = os.path.dirname(os.path.realpath(__file__))
    input = open(f"{script_path}/../data/20.txt", "r").read().strip()
    print(f"Part 1: {part1(input)}")
    # 831600 is too low
    print(f"Part 2: {part2(input)}")
