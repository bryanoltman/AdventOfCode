import Testing

@testable import AdventOfCode

@Suite("Day 1") struct Day01Tests {

  let input = """
    3   4
    4   3
    2   5
    1   3
    3   9
    3   3
    """

  @Test func ParsesInput() async throws {
    #expect(
      Day01(data: input).entities == [
        [3, 4],
        [4, 3],
        [2, 5],
        [1, 3],
        [3, 9],
        [3, 3],
      ])
  }

  @Test func Part1() async throws {
    #expect(Day01(data: input).part1() == 11)
  }

  @Test func Part2() async throws {
    #expect(Day01(data: input).part2() == 31)
  }
}
