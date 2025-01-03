import os


def parse_input(input):
    # Butterscotch: capacity -1, durability -2, flavor 6, texture 3, calories 8
    ret = []
    for line in input.split("\n"):
        (name, _, capacity, _, durability, _, flavor, _, texture, _, calories) = (
            line.split(" ")
        )
        strs = [capacity, durability, flavor, texture, calories]
        ints = [int(s.strip().replace(",", "")) for s in strs]
        ret.append(ints)

    return ret


def part1(input):
    parsed = parse_input(input)
    # Drop the last item because we ignore calories in the sum
    ingA = parsed[0][:-1]
    ingB = parsed[1][:-1]
    ingC = parsed[2][:-1]
    ingD = parsed[3][:-1]

    max_score = 0
    for a in range(100):
        for b in range(100):
            for c in range(100):
                for d in range(100):
                    if a + b + c + d != 100:
                        continue
                    score = 1
                    for i, j, k, l in zip(ingA, ingB, ingC, ingD):
                        sum = i * a + j * b + k * c + l * d
                        score *= max(0, sum)

                    if score > max_score:
                        max_score = score

    return max_score


def part2(input):
    parsed = parse_input(input)
    # Drop the last item because we ignore calories in the sum
    ingA = parsed[0][:-1]
    ingB = parsed[1][:-1]
    ingC = parsed[2][:-1]
    ingD = parsed[3][:-1]

    max_score = 0
    for a in range(100):
        for b in range(100):
            for c in range(100):
                for d in range(100):
                    if a + b + c + d != 100:
                        continue
                    # Same as last time, but cals must sum to 500. Because we
                    # drop cals in input parsing to make zipping easier below,
                    # we pull them from our parsed lists.
                    cals = (
                        a * parsed[0][-1]
                        + b * parsed[1][-1]
                        + c * parsed[2][-1]
                        + d * parsed[3][-1]
                    )
                    if cals != 500:
                        continue

                    score = 1
                    for i, j, k, l in zip(ingA, ingB, ingC, ingD):
                        sum = i * a + j * b + k * c + l * d
                        score *= max(0, sum)

                    if score > max_score:
                        max_score = score

    return max_score


if __name__ == "__main__":
    script_path = os.path.dirname(os.path.realpath(__file__))
    input = open(f"{script_path}/../data/15.txt", "r").read().strip()
    print(f"Part 1: {part1(input)}")
    print(f"Part 2: {part2(input)}")
