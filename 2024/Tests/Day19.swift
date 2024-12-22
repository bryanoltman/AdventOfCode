import Testing

@testable import AdventOfCode

@Suite("Day 19") struct Day19Tests {
  let input = """
    r, wr, b, g, bwu, rb, gb, br

    brwrr
    bggr
    gbbr
    rrbgbr
    ubwu
    bwurrg
    brgr
    bbrgwb
    """

  @Test func Part1() {
    #expect(Day19(data: input).part1() == 6)
  }

  @Test func Part2() {
    #expect(Day19(data: input).part2() == 16)
  }
}
