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


def asdf(n):

    pass


def gen_perms(n):
    perms = []
    prev_perm = []
    for _ in range(n):
        max = 100 if not prev_perm else prev_perm[-1]
        next_perm = [max - i for i in range(max + 1)]
        perms.append(next_perm)
        prev_perm = next_perm
    return perms


def part1(input):
    parsed = parse_input(input)
    perms = gen_perms(len(parsed))

    return 0


def part2(input):
    return 0


if __name__ == "__main__":
    script_path = os.path.dirname(os.path.realpath(__file__))
    input = open(f"{script_path}/../data/15.txt", "r").read().strip()
    print(f"Part 1: {part1(input)}")
    print(f"Part 2: {part2(input)}")
