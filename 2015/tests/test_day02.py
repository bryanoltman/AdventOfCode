from advent_of_code.src.day02 import part1, part2


def test_part1():
    assert part1(["2x3x4"]) == 58
    assert part1(["1x1x10"]) == 43


def test_part2():
    assert part2(["2x3x4"]) == 34
    assert part2(["1x1x10"]) == 14
