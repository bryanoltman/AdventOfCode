from day06 import part1, part2

input = """
COM)B
B)C
C)D
D)E
E)F
B)G
G)H
D)I
E)J
J)K
K)L
"""


def test_part1():
    assert part1(input) == 42


def test_part2():
    assert part2(input) == 4
