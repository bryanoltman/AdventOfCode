import Testing

@testable import AdventOfCode

@Suite("Day 25") struct Day25Tests {
  let input = """
    """

  @Test func Part1() {
    #expect(Day25(data: input).part1() == 0)
  }

  @Test func Part2() {
    #expect(Day25(data: input).part2() == 0)
  }
}
