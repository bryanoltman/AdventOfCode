import functools
import os

circuit = dict()


@functools.cache
def resolve(wire):
    if wire.isdigit():
        return int(wire)

    val = circuit[wire]
    if val.isdigit():
        return int(val)

    val_parts = val.split(" ")
    ret = None
    if len(val_parts) == 1:
        ret = resolve(val_parts[0])
    elif len(val_parts) == 2:
        if val_parts[0] == "NOT":
            ret = ~resolve(val_parts[1])
    elif len(val_parts) == 3:
        if val_parts[1] == "AND":
            ret = resolve(val_parts[0]) & resolve(val_parts[2])
        elif val_parts[1] == "OR":
            ret = resolve(val_parts[0]) | resolve(val_parts[2])
        elif val_parts[1] == "RSHIFT":
            ret = resolve(val_parts[0]) >> int(val_parts[2])
        elif val_parts[1] == "LSHIFT":
            ret = resolve(val_parts[0]) << int(val_parts[2])

    if ret is None:
        raise Exception("unmatched")

    return ret & 0xFFFF


def parse_input(input):
    circuit.clear()
    for line in input.strip().split("\n"):
        parts = line.split("->")
        inVal = parts[0].strip()
        outVal = parts[1].strip()
        circuit[outVal] = inVal


def part1(input):
    parse_input(input)
    return resolve("a")


def part2(input):
    parse_input(input)
    a_res = str(resolve("a"))
    resolve.cache_clear()
    parse_input(input)
    circuit["b"] = a_res
    return resolve("a")


if __name__ == "__main__":
    script_path = os.path.dirname(os.path.realpath(__file__))
    input = open(f"{script_path}/../data/07.txt", "r").read().strip()
    print(f"Part 1: {part1(input)}")
    print(f"Part 2: {part2(input)}")
