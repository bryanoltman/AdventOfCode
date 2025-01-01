def inclusive_range(start, stop):
    return range(start, stop + 1)


def range_intersect(r1, r2):
    return range(max(r1.start, r2.start), min(r1.stop, r2.stop)) or None


def merge_ranges(r1: range, r2: range) -> list[range]:
    if range_intersect(r1, r2) or r1.start == r2.stop or r2.start == r1.stop:
        return [range(min(r1.start, r2.start), max(r1.stop, r2.stop))]
    return [r1, r2]


def remove_range_from_range(r: range, target: range) -> list[range]:
    ret = []
    if r.start >= target.start and r.start <= target.stop:
        # target contains r's start
        if r.stop <= target.stop:
            # target contains r entirely.
            ret = [range(target.start, r.start), range(r.stop, target.stop)]
        else:
            # a cuts off the end of target
            ret = [range(target.start, r.start)]
    elif target.start >= r.start and target.start <= r.stop:
        # a contains target's start
        if target.stop < r.stop:
            # r contains target entirely
            ret = []
        else:
            # r cuts off target start
            ret = [range(r.stop, target.stop)]
    else:
        ret = [target]

    return [r for r in ret if r]


def flatten_ranges(ranges: list[range]) -> list[range]:
    ranges = sorted(ranges, key=lambda r: r.start)
    ranges = [r for r in ranges if r]
    i = 0
    while i < len(ranges) - 1:
        a = ranges[i]
        b = ranges[i + 1]
        merged = merge_ranges(a, b)
        if len(merged) == 1:
            # The merge did something
            ranges[i] = merged[0]
            del ranges[i + 1]
        else:
            i += 1

    return ranges
