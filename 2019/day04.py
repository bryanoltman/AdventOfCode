from more_itertools import windowed
import os


def is_good_password(pw):
    if len(pw) != 6:
        return False

    has_two_consec = False
    for a, b in windowed(pw, n=2):
        if a == b:
            has_two_consec = True
        if int(a) > int(b):
            return False

    if not has_two_consec:
        return False

    return True


def part1(input):
    lower_bound, upper_bound = input.split("-")
    return len(
        [
            pw
            for pw in range(int(lower_bound), int(upper_bound))
            if is_good_password(str(pw))
        ]
    )


def is_good_password_part2(pw):
    if not is_good_password(pw):
        return False

    current_digit = pw[0]
    num_repeating = 1
    for c in pw[1:]:
        if c == current_digit:
            num_repeating += 1
        else:
            if num_repeating == 2:
                return True
            num_repeating = 1
            current_digit = c

    return num_repeating == 2


def part2(input):
    lower_bound, upper_bound = input.split("-")
    return len(
        [
            pw
            for pw in range(int(lower_bound), int(upper_bound))
            if is_good_password_part2(str(pw))
        ]
    )


if __name__ == "__main__":
    script_path = os.path.dirname(os.path.realpath(__file__))
    input = open(f"{script_path}/data/04.txt", "r").read().strip()
    print(f"Part 1: {part1(input)}")
    print(f"Part 2: {part2(input)}")
