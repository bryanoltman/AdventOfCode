from collections import defaultdict
from itertools import permutations
import os
import re


def part1(input):
    people = set()
    distances = defaultdict(lambda: defaultdict(int))
    r = re.compile(r"(\w+) would (\w+) (\d+) happiness units by sitting next to (\w+)")
    for line in input.split("\n"):
        if not line:
            continue
        m = r.match(line)
        person_a = m.group(1)
        sign = 1 if m.group(2) == "gain" else -1
        units = int(m.group(3))
        person_b = m.group(4)
        people.add(person_a)
        people.add(person_b)
        distances[person_a][person_b] = sign * units

    max_happiness = 0
    for seating in permutations(people):
        happiness = 0
        for i in range(len(seating)):
            current = seating[i]
            left = seating[i - 1]
            right = seating[i + 1 if i + 1 < len(seating) else 0]
            happiness += distances[current][left]
            happiness += distances[current][right]
        if happiness > max_happiness:
            max_happiness = happiness

    return max_happiness


def part2(input):
    people = set()
    distances = defaultdict(lambda: defaultdict(int))
    r = re.compile(r"(\w+) would (\w+) (\d+) happiness units by sitting next to (\w+)")
    people.add("me")
    for line in input.split("\n"):
        if not line:
            continue
        m = r.match(line)
        person_a = m.group(1)
        sign = 1 if m.group(2) == "gain" else -1
        units = int(m.group(3))
        person_b = m.group(4)
        people.add(person_a)
        people.add(person_b)
        distances[person_a][person_b] = sign * units
        distances[person_a]["me"] = 0

    max_happiness = 0
    for seating in permutations(people):
        happiness = 0
        for i in range(len(seating)):
            current = seating[i]
            left = seating[i - 1]
            right = seating[i + 1 if i + 1 < len(seating) else 0]
            happiness += distances[current][left]
            happiness += distances[current][right]
        if happiness > max_happiness:
            max_happiness = happiness

    return max_happiness


if __name__ == "__main__":
    script_path = os.path.dirname(os.path.realpath(__file__))
    input = open(f"{script_path}/../data/13.txt", "r").read().strip()
    print(f"Part 1: {part1(input)}")
    print(f"Part 2: {part2(input)}")
