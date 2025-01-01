from advent_of_code.util.ranges import (
    flatten_ranges,
    merge_ranges,
    remove_range_from_range,
)


def test_merge_ranges():
    assert merge_ranges(range(1, 3), range(2, 4)) == [range(1, 4)]
    assert merge_ranges(range(1, 1), range(3, 4)) == [range(1, 1), range(3, 4)]
    assert merge_ranges(range(1, 5), range(3, 4)) == [range(1, 5)]
    assert merge_ranges(range(3, 4), range(1, 5)) == [range(1, 5)]


def test_remove_range_from_range():
    # a overlaps target at beginning
    assert remove_range_from_range(range(1, 3), range(2, 4)) == [range(3, 4)]

    # a overlaps target at end
    assert remove_range_from_range(range(2, 4), range(1, 3)) == [range(1, 2)]

    # a is fully separate from target
    assert remove_range_from_range(range(1, 2), range(2, 4)) == [range(2, 4)]

    # a is fully contained in target
    assert remove_range_from_range(range(3, 4), range(1, 5)) == [
        range(1, 3),
        range(4, 5),
    ]

    assert remove_range_from_range(range(887, 898), range(887, 960)) == [
        range(898, 960)
    ]


def test_flatten_ranges():
    assert flatten_ranges([range(1, 2), range(2, 3), range(1, 4)]) == [range(1, 4)]
    assert flatten_ranges([range(1, 2), range(2, 3)]) == [range(1, 3)]
    assert flatten_ranges([range(1, 2), range(3, 4)]) == [range(1, 2), range(3, 4)]
    assert flatten_ranges([range(1, 2), range(2, 3), range(3, 4)]) == [range(1, 4)]
    assert flatten_ranges([range(1, 2), range(2, 3), range(4, 5)]) == [
        range(1, 3),
        range(4, 5),
    ]
    assert flatten_ranges([range(1, 2), range(3, 4), range(2, 3)]) == [range(1, 4)]
    assert flatten_ranges([range(1, 2), range(3, 4), range(5, 6)]) == [
        range(1, 2),
        range(3, 4),
        range(5, 6),
    ]
    assert flatten_ranges([range(1, 2), range(3, 4), range(2, 3), range(5, 6)]) == [
        range(1, 4),
        range(5, 6),
    ]
    assert flatten_ranges(
        [range(1, 2), range(3, 4), range(2, 3), range(5, 6), range(4, 5)]
    ) == [range(1, 6)]
