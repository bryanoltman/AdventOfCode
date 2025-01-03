from advent_of_code.src.day17 import (
    count_container_combos,
    find_container_combos,
)

sizes = [20, 15, 10, 5, 5]


def test_find_container_combos():
    assert find_container_combos(sizes, 25) == 4


def test_count_container_combos():
    assert count_container_combos(sizes, 25) == 3
