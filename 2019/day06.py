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


def search(seen, current_node, target_node) -> int:
    seen.add(current_node)
    neighbors = list(current_node.orbited_by)
    if current_node.orbits:
        neighbors.append(current_node.orbits)
    for n in [n for n in neighbors if n not in seen]:
        if n is target_node:
            return 1
        val = search(seen, n, target_node)
        if val:
            return val + 1
    return 0


def part2(input):
    start = "YOU"
    end = "SAN"
    nodes = parse_map(input)
    start_node = nodes[start]
    end_node = nodes[end]
    path_length = search(set(), start_node, end_node)
    # This is technically from start's parent to end's parent, so substract
    # start and end
    return path_length - 2


if __name__ == "__main__":
    script_path = os.path.dirname(os.path.realpath(__file__))
    input = open(f"{script_path}/data/06.txt", "r").read().strip()
    print(f"Part 1: {part1(input)}")
    print(f"Part 2: {part2(input)}")
