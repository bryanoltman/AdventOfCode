import Testing

@testable import AdventOfCode

@Suite("Day 11") struct Day11Tests {
  let input = "125 17"

  @Test func Part1() {
    let day = Day11(data: input)
    #expect(day.part1() == 55312)
  }

  @Test func Part2() {
    let day = Day11(data: input)
    #expect(day.part2() == 65601038650482)
  }
}
