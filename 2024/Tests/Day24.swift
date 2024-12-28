import Testing

@testable import AdventOfCode

@Suite("Day 24") struct Day24Tests {
  let input = """
    """

  @Test func Part1() {
    #expect(Day24(data: input).part1() == 0)
  }

  @Test func Part2() {
    #expect(Day24(data: input).part2() == 0)
  }
}
