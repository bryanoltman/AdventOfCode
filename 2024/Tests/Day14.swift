import Testing

@testable import AdventOfCode

@Suite("Day 14") struct Day14Tests {

  let input = """
    """

  @Test func Part1() async throws {
    #expect(Day14(data: input).part1() == 0)
  }

  @Test func Part2() async throws {
    #expect(Day14(data: input).part2() == 0)
  }
}
