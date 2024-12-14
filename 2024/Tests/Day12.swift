import Testing

@testable import AdventOfCode

@Suite("Day 12") struct Day12Tests {
    let input = """
      RRRRIICCFF
      RRRRIICCCF
      VVRRRCCFFF
      VVRCCCJFFF
      VVVVCJJCFE
      VVIVCCJJEE
      VVIIICJJEE
      MIIIIIJJEE
      MIIISIJEEE
      MMMISSJEEE
      """

  @Test func Part1() async throws {
    #expect(Day12(data: input).part1() == 1930)
  }

  @Test func Part2() async throws {
    #expect(Day12(data: input).part2() == 1206)
  }
}
