from itertools import chain
import os


def parse_input(input):
    (replacements, molecule) = input.split("\n\n")
    replacment_map = [
        (parts[0], parts[1])
        for parts in [x.split(" => ") for x in replacements.split("\n")]
    ]
    return (replacment_map, molecule.strip())


def all_replacements(replacements, molecule):
    ret = set()
    for k, v in replacements:
        i = 0
        while True:
            instance_idx = molecule.find(k, i)
            if instance_idx == -1:
                break
            new_str = molecule[:instance_idx] + v + molecule[instance_idx + len(k) :]
            ret.add(new_str)
            i = instance_idx + 1

    return ret


def part1(input):
    (replacements, molecule) = parse_input(input)
    ret = all_replacements(replacements, molecule)
    return len(ret)


def part2(input):
    (replacements, molecule) = parse_input(input)
    new_molecules = all_replacements(replacements, "e")
    i = 0
    while molecule not in new_molecules:
        next_evolution = set()
        for m in new_molecules:
            next_evolution.update(all_replacements(replacements, m))
        new_molecules = next_evolution
        i += 1

    return i


if __name__ == "__main__":
    script_path = os.path.dirname(os.path.realpath(__file__))
    input = open(f"{script_path}/../data/19.txt", "r").read().strip()
    print(f"Part 1: {part1(input)}")
    print(f"Part 2: {part2(input)}")
