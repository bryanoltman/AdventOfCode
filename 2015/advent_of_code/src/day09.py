from collections import defaultdict
from itertools import permutations
import os
import sys


def part1(input):
    places = set()
    distances = defaultdict(lambda: defaultdict(int))
    for line in input.split("\n"):
        (a, _, b, _, dist) = line.split()
        places.add(a)
        places.add(b)
        distances[a][b] = int(dist)
        distances[b][a] = int(dist)
    min_distance = sys.maxsize
    for path in permutations(places):
        d = 0
        for i in range(len(path) - 1):
            a = path[i]
            b = path[i + 1]
            d += distances[a][b]

        if d < min_distance:
            min_distance = d

    return min_distance


def part2(input):
    places = set()
    distances = defaultdict(lambda: defaultdict(int))
    for line in input.split("\n"):
        (a, _, b, _, dist) = line.split()
        places.add(a)
        places.add(b)
        distances[a][b] = int(dist)
        distances[b][a] = int(dist)
    max_distance = 0
    for path in permutations(places):
        d = 0
        for i in range(len(path) - 1):
            a = path[i]
            b = path[i + 1]
            d += distances[a][b]

        if d > max_distance:
            max_distance = d

    return max_distance


if __name__ == "__main__":
    script_path = os.path.dirname(os.path.realpath(__file__))
    input = open(f"{script_path}/../data/09.txt", "r").read().strip()
    print(f"Part 1: {part1(input)}")
    print(f"Part 2: {part2(input)}")
