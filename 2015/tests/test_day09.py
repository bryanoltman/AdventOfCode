from advent_of_code.src.day09 import (
    part1,
    part2,
)


def test_part1():
    input = """London to Dublin = 464
London to Belfast = 518
Dublin to Belfast = 141"""
    assert part1(input) == 605


def test_part2():
    input = """London to Dublin = 464
London to Belfast = 518
Dublin to Belfast = 141"""
    assert part2(input) == 982
