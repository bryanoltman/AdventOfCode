import Testing

@testable import AdventOfCode

@Suite("Day 20") struct Day20Tests {
  let input = """
    ###############
    #...#...#.....#
    #.#.#.#.#.###.#
    #S#...#.#.#...#
    #######.#.#.###
    #######.#.#...#
    #######.#.###.#
    ###..E#...#...#
    ###.#######.###
    #...###...#...#
    #.#####.#.###.#
    #.#...#.#.#...#
    #.#.#.#.#.#.###
    #...#...#...###
    ###############
    """

  @Test func Part1() {
    #expect(Day20(data: input).part1() == 0)
  }

  @Test func Part2() {
    #expect(Day20(data: input).part2() == 0)
  }
}
