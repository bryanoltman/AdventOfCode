import Testing

@testable import AdventOfCode

@Suite("Day 16") struct Day16Tests {
  let input = """
    """

  @Test func Part1() {
    #expect(Day16(data: input).part1() == 0)
  }

  @Test func Part2() {
    #expect(Day16(data: input).part2() == 0)
  }
}
