from enum import Enum
import os
import re


class Operation(Enum):
    TOGGLE = 1
    TURN_ON = 2
    TURN_OFF = 3


class Instruction:
    def __init__(self, operation, x_range, y_range):
        self.operation = operation
        self.x_range = x_range
        self.y_range = y_range

    def parse_from_line(line: str):
        turn_on_regex = re.compile(r"turn on (\d+),(\d+) through (\d+),(\d+)")
        turn_off_regex = re.compile(r"turn off (\d+),(\d+) through (\d+),(\d+)")
        toggle_regex = re.compile(r"toggle (\d+),(\d+) through (\d+),(\d+)")
        op = None

        if turn_on_regex.match(line):
            op = Operation.TURN_ON
            m = turn_on_regex.match(line)
        elif turn_off_regex.match(line):
            op = Operation.TURN_OFF
            m = turn_off_regex.match(line)
        elif toggle_regex.match(line):
            op = Operation.TOGGLE
            m = toggle_regex.match(line)

        if not op:
            raise Exception("no op found")

        x_range = range(int(m.group(1)), int(m.group(3)) + 1)
        y_range = range(int(m.group(2)), int(m.group(4)) + 1)
        return Instruction(op, x_range, y_range)


def range_intersect(r1, r2):
    return range(max(r1.start, r2.start), min(r1.stop, r2.stop)) or None


def merge_ranges(a, b):
    return range(min(a.start, b.start), max(a.stop, b.stop))


def add_range(r: range, lines: list[range]) -> list[range]:
    """
    Adds line a to b. If they are disjoint (i.e., don't share a y axis),
    a and b will be returned separately
    """
    new_ranges = []
    found_overlap = False
    for b in lines:
        lines_overlap = range_intersect(r, b) is not None
        if not lines_overlap:
            new_ranges.append(b)
        else:
            new_ranges.append(merge_ranges(r, b))
            found_overlap = True

    # If we didn't combine this into an existing range, add it to the list
    if not found_overlap:
        new_ranges.append(r)

    return new_ranges


def remove_range_from_range(a: range, target: range) -> list[range]:
    if a.start >= target.start and a.start <= target.stop:
        # target contains a's start
        if a.stop <= target.stop:
            # target contains a entirely
            return [range(target.start, a.start), range(a.stop, target.stop)]
        else:
            # a cuts off the end of target
            return [range(target.start, a.start)]
    elif target.start >= a.start and target.start <= a.stop:
        # a contains target's start
        if target.stop <= a.stop:
            # a contains target entirely
            return []
        else:
            # a cuts off target start
            return [range(a.stop, target.stop)]
    return [target]


def remove_range(r: range, ranges: list[range]) -> list[range]:
    new_ranges = []
    for b in ranges:
        lines_overlap = range_intersect(r, b) is not None
        if not lines_overlap:
            new_ranges.append(b)
        else:
            new_ranges.extend(remove_range_from_range(r, b))

    return new_ranges


def toggle_range(r: range, ranges: list[range]) -> list[range]:
    new_ranges = []
    found_overlap = False
    for b in ranges:
        intersection = range_intersect(r, b)
        lines_overlap = intersection is not None
        if not lines_overlap:
            new_ranges.append(b)
        else:
            found_overlap = True
            new_ranges.extend(remove_range_from_range(intersection, b))
            if r.start < b.start:
                new_ranges.extend(range(r.start, b.start))
            if r.stop > b.stop:
                new_ranges.extend(range(b.stop, r.stop))

    if not found_overlap:
        new_ranges.append(r)

    return new_ranges


def part1(input):
    lines = filter(len, input.splitlines())
    instructions = [Instruction.parse_from_line(l.strip()) for l in lines]
    lines = [[]] * 1000
    for i in instructions:
        for y in i.y_range:
            if i.operation is Operation.TOGGLE:
                lines[y] = toggle_range(i.x_range, lines[y])
            elif i.operation is Operation.TURN_ON:
                lines[y] = add_range(i.x_range, lines[y])
            else:
                lines[y] = remove_range(i.x_range, lines[y])

    # Merge ranges in line
    for i in range(len(lines)):
        ranges = sorted(lines[i], key=lambda r: r.start)
        new_line = []
        current_range = None
        for r in ranges:
            if not current_range:
                current_range = r
                continue
            if range_intersect(current_range, r) is None:
                new_line.append(current_range)
                current_range = r
            else:
                current_range = range(current_range.start, r.stop)
        new_line.append(current_range)

        lines[i] = new_line

    on_light_count = 0
    for l in lines:
        for r in l:
            on_light_count += len(r)

    return on_light_count


def part2(input):
    return 0


if __name__ == "__main__":
    # 325000 is too low
    script_path = os.path.dirname(os.path.realpath(__file__))
    input = open(f"{script_path}/../data/06.txt", "r").read().strip()
    print(f"Part 1: {part1(input)}")
    print(f"Part 2: {part2(input)}")
