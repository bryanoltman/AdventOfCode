import os


def parse_aunts(input):
    ret = []
    for line in input.split("\n"):
        if not line:
            continue
        first_colon = line.find(":")
        line = line[first_colon + 1 :]
        props = line.split(",")
        aunt_sue = {}
        for v in props:
            (key, val) = v.split(":")
            aunt_sue[key.strip()] = int(val.strip())
        ret.append(aunt_sue)

    return ret


criteria = {
    "children": 3,
    "cats": 7,
    "samoyeds": 2,
    "pomeranians": 3,
    "akitas": 0,
    "vizslas": 0,
    "goldfish": 5,
    "trees": 3,
    "cars": 2,
    "perfumes": 1,
}


def part1(input):
    aunts = parse_aunts(input)

    candidates = []
    for i, sue in enumerate(aunts):
        is_candidate = True
        for k, v in criteria.items():
            if k in sue and sue[k] != v:
                is_candidate = False
                break
        if is_candidate:
            candidates.append(i)

    if len(candidates) != 1:
        raise Exception("too many sues")

    # +1 because Sues are 1-indexed
    return candidates[0] + 1


def part2(input):
    aunts = parse_aunts(input)

    candidates = []
    for i, sue in enumerate(aunts):
        is_candidate = True
        for k, v in criteria.items():
            if k not in sue:
                continue

            if k == "cats" or k == "trees":
                if sue[k] <= v:
                    is_candidate = False
                    break
            elif k == "pomeranians" or k == "goldfish":
                if sue[k] >= v:
                    is_candidate = False
                    break
            elif sue[k] != v:
                is_candidate = False
                break
        if is_candidate:
            candidates.append(i)

    if len(candidates) != 1:
        raise Exception("too many sues")

    # +1 because Sues are 1-indexed
    return candidates[0] + 1


if __name__ == "__main__":
    script_path = os.path.dirname(os.path.realpath(__file__))
    input = open(f"{script_path}/../data/16.txt", "r").read().strip()
    print(f"Part 1: {part1(input)}")
    print(f"Part 2: {part2(input)}")
