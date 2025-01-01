import os


def spot_to_str(spot):
    return f"{spot[0]}_{spot[1]}"


def part1(input):
    spots = set()
    current_spot = (0, 0)
    for dir in input:
        spots |= {spot_to_str(current_spot)}
        if dir == ">":
            current_spot = (current_spot[0] + 1, current_spot[1])
        elif dir == "^":
            current_spot = (current_spot[0], current_spot[1] + 1)
        elif dir == "<":
            current_spot = (current_spot[0] - 1, current_spot[1])
        elif dir == "v":
            current_spot = (current_spot[0], current_spot[1] - 1)
    spots |= {spot_to_str(current_spot)}
    return len(spots)


def move_spot(spot, dir):
    if dir == ">":
        return (spot[0] + 1, spot[1])
    elif dir == "^":
        return (spot[0], spot[1] + 1)
    elif dir == "<":
        return (spot[0] - 1, spot[1])
    elif dir == "v":
        return (spot[0], spot[1] - 1)


def part2(input):
    spots = set()
    santa_spot = (0, 0)
    robo_santa_spot = (0, 0)
    spots |= {spot_to_str(santa_spot)}
    is_santa_turn = True
    for dir in input:
        if is_santa_turn:
            santa_spot = move_spot(santa_spot, dir)
            spots |= {spot_to_str(santa_spot)}
        else:
            robo_santa_spot = move_spot(robo_santa_spot, dir)
            spots |= {spot_to_str(robo_santa_spot)}
        is_santa_turn = not is_santa_turn
    return len(spots)


if __name__ == "__main__":
    script_path = os.path.dirname(os.path.realpath(__file__))
    input = open(f"{script_path}/../data/03.txt", "r").read()
    print(f"Part 1: {part1(input)}")
    print(f"Part 2: {part2(input)}")
