from day02 import part1


def test_part1():
    assert part1("1,0,0,0,99") == 2
    assert part1("2,3,0,3,99") == 2
    assert part1("2,4,4,5,99,0") == 2
    assert part1("1,1,1,4,99,5,6,0,99") == 30
