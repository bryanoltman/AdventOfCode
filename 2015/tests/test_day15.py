from advent_of_code.src.day15 import (
    part1,
)

input = """Butterscotch: capacity -1, durability -2, flavor 6, texture 3, calories 8
Cinnamon: capacity 2, durability 3, flavor -2, texture -1, calories 3
"""


def test_part1():
    assert part1(input) == 62842880
