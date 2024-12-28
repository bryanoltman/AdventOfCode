import Testing

@testable import AdventOfCode

@Suite("Day 23") struct Day23Tests {
  let input = """
    """

  @Test func Part1() {
    #expect(Day23(data: input).part1() == 0)
  }

  @Test func Part2() {
    #expect(Day23(data: input).part2() == 0)
  }
}
