from collections import defaultdict
import os

bad_substrs = {"ab", "cd", "pq", "xy"}
vowels = {"a", "e", "i", "o", "u"}


def is_good_str_part1(str):
    vowel_count = 0

    has_repeating_char = False
    for i, char in enumerate(str):
        if char in vowels:
            vowel_count += 1
        if i == len(str) - 1:
            break
        next_char = str[i + 1]
        if char == next_char:
            has_repeating_char = True

    if not has_repeating_char:
        return False

    if vowel_count < 3:
        return False

    for substr in bad_substrs:
        if substr in str:
            return False

    return True


def part1(input):
    lines = input.splitlines()
    num_good_strs = 0
    for l in lines:
        if is_good_str_part1(l):
            num_good_strs += 1

    return num_good_strs


def is_good_str_part2(str):
    last_pair_idx = defaultdict(list)
    has_repeating_letter = False
    has_repeating_pair = False
    for i, char in enumerate(str):
        if i + 2 < len(str):
            if char == str[i + 2]:
                has_repeating_letter = True
        if i + 1 < len(str):
            pair = f"{char}{str[i + 1]}"
            if last_pair_idx[pair] and last_pair_idx[pair][0] != i - 1:
                has_repeating_pair = True
            last_pair_idx[pair].append(i)

    return has_repeating_letter and has_repeating_pair


def part2(input):
    lines = input.splitlines()
    num_good_strs = 0
    for l in lines:
        if is_good_str_part2(l):
            num_good_strs += 1

    return num_good_strs


if __name__ == "__main__":
    script_path = os.path.dirname(os.path.realpath(__file__))
    input = open(f"{script_path}/../data/05.txt", "r").read().strip()
    print(f"Part 1: {part1(input)}")
    print(f"Part 2: {part2(input)}")
