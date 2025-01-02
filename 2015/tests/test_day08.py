from advent_of_code.src.day08 import (
    encoded_str_len,
    part1,
    chars_in_str,
    part2,
)


def test_part1():
    assert chars_in_str(r'""') == 0
    assert chars_in_str(r'"abc"') == 3
    assert chars_in_str(r'"aaa\"aaa"') == 7
    assert chars_in_str(r'"\x27"') == 1
    input = r"""""
"abc"
"aaa\"aaa"
"\x27"
"""
    assert part1(input) == 12


def test_part2():
    input = r"""""
"abc"
"aaa\"aaa"
"\x27"
"""
    assert encoded_str_len(r'""') == 6
    assert encoded_str_len(r'"abc"') == 9
    assert encoded_str_len(r'"aaa\"aaa"') == 16
    assert encoded_str_len(r'"\x27"') == 11
    assert part2(input) == 19
