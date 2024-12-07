import Testing

@testable import AdventOfCode

@Suite("Day 7") struct Day07Tests {

  let input = """
    190: 10 19
    3267: 81 40 27
    83: 17 5
    156: 15 6
    7290: 6 8 6 15
    161011: 16 10 13
    192: 17 8 14
    21037: 9 7 18 13
    292: 11 6 16 20
    """

  @Test func ParsesInput() {
    let day07 = Day07(data: input)
    #expect(day07.input.rows.count == 8)
    #expect(day07.input.rows[0].total == 190)
  }

  @Test func Part1() {
    #expect(Day07(data: input).part1() == 3749)
  }

  @Test func Part2() {
    #expect(Day07(data: input).part2() == 11387)
  }
}
