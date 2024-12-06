import Testing

@testable import AdventOfCode

@Suite("Day 6") struct Day06Tests {

  let input = """
    ....#.....
    .........#
    ..........
    ..#.......
    .......#..
    ..........
    .#..^.....
    ........#.
    #.........
    ......#...
    """

  @Test func ParsesInput() async throws {
    let day6 = Day06(data: input)
    #expect(day6.grid.findFirst(item: "^") == Point(x: 4, y: 6))
  }

  @Test func Part1() async throws {
    #expect(Day06(data: input).part1() == 41)
  }

  @Test func Part2() async throws {
    #expect(Day06(data: input).part2() == 6)
  }
}
