import os


class Node:
    def __init__(self, name: str):
        self.name = name
        self.orbits = None
        self.orbited_by = set()


def parse_map(input):
    nodes = {}
    for line in input.splitlines():
        if not line:
            continue
        (orbitee_name, orbiter_name) = line.split(")")
        if orbitee_name not in nodes:
            nodes[orbitee_name] = Node(orbitee_name)
        if orbiter_name not in nodes:
            nodes[orbiter_name] = Node(orbiter_name)
        orbiter = nodes[orbiter_name]
        orbitee = nodes[orbitee_name]
        orbiter.orbits = orbitee
        orbitee.orbited_by.add(orbiter)
    return nodes


def count_indirect_orbits(node) -> int:
    parent = node.orbits
    ret = 0
    while parent and parent.orbits:
        ret += 1
        parent = parent.orbits
    return ret


def part1(input):
    nodes = parse_map(input)
    direct_orbits = len([n for n in nodes.values() if n.orbits is not None])
    indirect_orbits = sum([count_indirect_orbits(n) for n in nodes.values()])
    return direct_orbits + indirect_orbits


def part2(input):
    return 0


if __name__ == "__main__":
    script_path = os.path.dirname(os.path.realpath(__file__))
    input = open(f"{script_path}/data/06.txt", "r").read().strip()
    print(f"Part 1: {part1(input)}")
    print(f"Part 2: {part2(input)}")
