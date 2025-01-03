from collections import defaultdict
from itertools import permutations
import os
import re


class Reindeer:
    def __init__(self, name, speed, fly_secs, rest_secs):
        self.name = name
        self.speed = speed
        self.fly_secs = fly_secs
        self.rest_secs = rest_secs


def parse_input(input):
    # ex:
    # Vixen can fly 8 km/s for 8 seconds, but then must rest for 53 seconds.
    r = re.compile(
        r"(\w+) can fly (\d+) km\/s for (\d+) seconds, but then must rest for (\d+) seconds"
    )
    deer = []
    for line in input.split("\n"):
        if not line:
            continue
        m = r.match(line)
        deer.append(
            Reindeer(
                name=m.group(1),
                speed=int(m.group(2)),
                fly_secs=int(m.group(3)),
                rest_secs=int(m.group(4)),
            )
        )
    return deer


def dist_at_sec(deer, sec):
    dist_per_cycle = deer.fly_secs * deer.speed
    cycle_time = deer.fly_secs + deer.rest_secs
    cycles = sec // cycle_time
    dist = cycles * dist_per_cycle
    remaining_time = sec % cycle_time
    dist += deer.speed * min(remaining_time, deer.fly_secs)
    return dist


def part1(input):
    deer = parse_input(input)
    secs = 2503
    return max([dist_at_sec(d, secs) for d in deer])


def part2(input):
    deer = parse_input(input)
    secs = 2503
    scores = defaultdict(int)

    for i in range(secs):
        distances = {d: dist_at_sec(d, i + 1) for d in deer}
        max_dist = max(distances.values())
        for d, dist in distances.items():
            if dist == max_dist:
                scores[d] += 1

    return max(scores.values())


if __name__ == "__main__":
    script_path = os.path.dirname(os.path.realpath(__file__))
    input = open(f"{script_path}/../data/14.txt", "r").read().strip()
    print(f"Part 1: {part1(input)}")
    print(f"Part 2: {part2(input)}")
