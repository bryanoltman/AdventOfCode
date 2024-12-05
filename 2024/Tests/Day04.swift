import Testing

@testable import AdventOfCode

@Suite("Day 4") struct Day04Tests {
  let input = """
MMMSXXMASM
MSAMXMSMSA
AMXSXMAAMM
MSAMASMSMX
XMASAMXAMM
XXAMMXXAMA
SMSMSASXSS
SAXAMASAAA
MAMMMXMMMM
MXMXAXMASX
"""

  @Test func ParsesInput() {
    #expect(Day04(data: input).grid == [
      ["M", "M", "M", "S", "X", "X", "M", "A", "S", "M"],
      ["M", "S", "A", "M", "X", "M", "S", "M", "S", "A"],
      ["A", "M", "X", "S", "X", "M", "A", "A", "M", "M"],
      ["M", "S", "A", "M", "A", "S", "M", "S", "M", "X"],
      ["X", "M", "A", "S", "A", "M", "X", "A", "M", "M"],
      ["X", "X", "A", "M", "M", "X", "X", "A", "M", "A"],
      ["S", "M", "S", "M", "S", "A", "S", "X", "S", "S"],
      ["S", "A", "X", "A", "M", "A", "S", "A", "A", "A"],
      ["M", "A", "M", "M", "M", "X", "M", "M", "M", "M"],
      ["M", "X", "M", "X", "A", "X", "M", "A", "S", "X"],
    ])
  }

  @Test func Part1() {
    #expect(Day04(data: input).part1() == 18)
  }

  @Test func Part2() {
    #expect(Day04(data: input).part2() == 9)
  }
}
