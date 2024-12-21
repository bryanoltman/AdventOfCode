import Testing

@testable import AdventOfCode

@Suite("Day 17") struct Day17Tests {
  let input = """
    Register A: 729
    Register B: 0
    Register C: 0

    Program: 0,1,5,4,3,0
    """

  @Test func Part1() {
    #expect(Day17(data: input).part1() == 0)
  }

  @Test func Part2() {
    #expect(Day17(data: input).part2() == 0)
  }
}
