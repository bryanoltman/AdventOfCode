import os


# Returns a list of (character, number_of_repetitions)
# This is the "look-and-say" sequence
# ex: [("1", 2), ("3", 1), ("2", 4)] turns into 1132222
# ("two ones", "one three", "four twos")
def parse(input) -> list[tuple[int, str]]:
    counts = []
    running_char = (0, input[0])
    for i in range(len(input)):
        if running_char[1] == input[i]:
            running_char = (running_char[0] + 1, running_char[1])
        else:
            counts.append(running_char)
            running_char = (1, input[i])
    counts.append(running_char)
    return counts


def evolve(counts):
    evolved = []
    for num, char in counts:
        evolved.append((1, f"{num}"))
        evolved.append((1, char))

    # Compact the counts (`(1,1), (1,1)` becomes `(2,1)`)
    new_counts = []
    running_count = None
    for num, char in evolved:
        if running_count and running_count[1] == char:
            running_count = (num + running_count[0], running_count[1])
        else:
            if running_count:
                new_counts.append(running_count)
            running_count = (num, char)

    new_counts.append(running_count)
    return new_counts


def part1(input):
    counts = parse(input)

    num_generations = 40
    for _ in range(num_generations):
        counts = evolve(counts)
    return sum(c[0] for c in counts)


def part2(input):
    counts = parse(input)

    num_generations = 50
    for _ in range(num_generations):
        counts = evolve(counts)
    return sum(c[0] for c in counts)


if __name__ == "__main__":
    script_path = os.path.dirname(os.path.realpath(__file__))
    input = open(f"{script_path}/../data/10.txt", "r").read().strip()
    print(f"Part 1: {part1(input)}")
    print(f"Part 2: {part2(input)}")
