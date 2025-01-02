from advent_of_code.src.day11 import (
    part1,
    is_valid_code,
)


def test_is_valid_code():
    assert not is_valid_code("hijklmmn")
    assert not is_valid_code("abbceffg")
    assert not is_valid_code("abbcegjk")
    assert not is_valid_code("abcdefgh")
    assert is_valid_code("abcdffaa")
    assert not is_valid_code("ghijklmn")
    assert is_valid_code("ghjaabcc")
    assert not is_valid_code("abcdeggg")


def test_part1():
    assert part1("abcdefgh") == "abcdffaa"
    assert part1("ghijklmn") == "ghjaabcc"
