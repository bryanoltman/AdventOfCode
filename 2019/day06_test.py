from day06 import part1

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
