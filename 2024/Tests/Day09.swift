import Testing

@testable import AdventOfCode

@Suite("Day 9") struct Day09Tests {
  let input = "2333133121414131402"

  @Test func Part1() {
    #expect(Day09(data: input).part1() == 1928)
  }

  @Test func Part2() {
    #expect(Day09(data: input).part2() == 2858)
  }
}
