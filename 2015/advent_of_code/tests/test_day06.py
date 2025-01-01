from advent_of_code.src.day06 import part1, part2, toggle_range


def test_part1():
    input = """
turn on 0,0 through 999,999
toggle 0,0 through 999,0
turn off 499,499 through 500,500
"""
    assert part1(input) == 1_000_000 - 1000 - 4


def test_part2():
    pass
