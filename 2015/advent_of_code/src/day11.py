import os
import more_itertools as mit


a_code = ord("a")
z_code = ord("z")


def is_valid_code(code: str) -> bool:
    if "i" in code or "o" in code or "l" in code:
        return False

    has_ordered_str = False
    for i, c in enumerate(code):
        if i + 2 >= len(code):
            break
        a = ord(c)
        b = ord(code[i + 1])
        c = ord(code[i + 2])
        if a + 1 == b and b + 1 == c:
            has_ordered_str = True
    if not has_ordered_str:
        return False

    num_pairs = 0
    last_pair_idx = None
    for i, (a, b) in enumerate(mit.windowed(code, n=2, step=1)):
        if last_pair_idx == i - 1:
            continue
        if a == b:
            num_pairs += 1
            last_pair_idx = i

    return num_pairs >= 2


def increment_base_26(string) -> str:
    new_pw = ""
    is_carrying = True
    for c in string[::-1]:
        new_digit = ord(c)
        if is_carrying:
            new_digit = ord(c) + 1
            if new_digit > z_code:
                new_digit = a_code
                is_carrying = True
            else:
                is_carrying = False
        new_pw += chr(new_digit)

    return new_pw[::-1]


def part1(input):
    current_pw = input
    while not is_valid_code(current_pw):
        current_pw = increment_base_26(current_pw)
    return current_pw


def part2(input):
    current_pw = input
    while not is_valid_code(current_pw):
        current_pw = increment_base_26(current_pw)
    current_pw = increment_base_26(current_pw)
    while not is_valid_code(current_pw):
        current_pw = increment_base_26(current_pw)
    return current_pw


if __name__ == "__main__":
    script_path = os.path.dirname(os.path.realpath(__file__))
    input = open(f"{script_path}/../data/11.txt", "r").read().strip()
    print(f"Part 1: {part1(input)}")
    print(f"Part 2: {part2(input)}")
