from collections import defaultdict
from itertools import combinations
import os


def find_container_combos(containers, target):
    ret = 0
    for i in range(len(containers)):
        for container_perm in combinations(containers, i):
            if sum(container_perm) == target:
                ret += 1
    return ret


def part1(input):
    containers = [int(x) for x in input.split("\n") if x]
    return find_container_combos(containers, 150)


def count_container_combos(containers, target):
    ret = defaultdict(int)
    for i in range(len(containers)):
        for container_perm in combinations(containers, i):
            if sum(container_perm) == target:
                ret[len(container_perm)] += 1
    return ret[min(ret.keys())]


def part2(input):
    containers = [int(x) for x in input.split("\n") if x]
    return count_container_combos(containers, 150)


if __name__ == "__main__":
    sizes = [20, 15, 10, 5, 5]
    find_container_combos(sizes, 25)

    script_path = os.path.dirname(os.path.realpath(__file__))
    input = open(f"{script_path}/../data/17.txt", "r").read().strip()
    print(f"Part 1: {part1(input)}")
    print(f"Part 2: {part2(input)}")
