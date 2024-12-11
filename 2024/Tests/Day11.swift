import Testing

@testable import AdventOfCode

@Suite("Day 11") struct Day11Tests {
  let input = """
    89010123
    78121874
    87430965
    96549874
    45678903
    32019012
    01329801
    10456732
    """


  @Test func Part1() {
    let day = Day11(data: input)
    #expect(day.part1() == 0)
  }

  @Test func Part2() {
    let day = Day11(data: input)
    #expect(day.part2() == 0)
  }
}
