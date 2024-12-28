import Testing

@testable import AdventOfCode

@Suite("Day 21") struct Day21Tests {
  let input = """
    029A
    980A
    179A
    456A
    379A
    """

  @Test func Part1() {
    #expect(Day21(data: input).part1() == 126384)
  }

  @Test func Part2() {
    #expect(Day21(data: input).part2() == 0)
  }
}
