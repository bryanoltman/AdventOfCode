from advent_of_code.src.day12 import (
    part1,
    part2,
)


def test_part1():
    assert part1("[1,2,3]") == 6
    assert part1('{"a":2,"b":4}') == 6


def test_part2():
    assert part2("[1,2,3]") == 6
    assert part2('[1,{"c":"red","b":2},3]') == 4
