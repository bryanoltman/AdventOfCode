import Testing

@testable import AdventOfCode

@Suite("Day 2") struct Day02Tests {
  let input = """
    7 6 4 2 1
    1 2 7 8 9
    9 7 6 2 1
    1 3 2 4 5
    8 6 4 4 1
    1 3 6 7 9
    """

  @Test func ParsesInput() async throws {
    #expect(
      Day02(data: input).entities == [
        [7, 6, 4, 2, 1],
        [1, 2, 7, 8, 9],
        [9, 7, 6, 2, 1],
        [1, 3, 2, 4, 5],
        [8, 6, 4, 4, 1],
        [1, 3, 6, 7, 9],
      ]
    )
  }

  @Test func Part1() async throws {
    #expect(Day02(data: input).part1() == 2)
  }

  @Test func Part2() async throws {
    #expect(Day02(data: input).part2() == 4)
  }
}
