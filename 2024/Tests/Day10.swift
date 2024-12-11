import Testing

@testable import AdventOfCode

@Suite("Day 10") struct Day10Tests {
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
    let day = Day10(data: input)
    #expect(day.trailheads.count == 9)
    #expect(day.part1() == 36)
  }

  @Test func Part2() {
    #expect(Day10(data: input).part2() == 81)
  }
}
