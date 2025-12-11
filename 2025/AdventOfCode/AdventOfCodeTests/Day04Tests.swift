import Testing

@testable import AdventOfCode

struct Day04Tests {
  let input = """
    ..@@.@@@@.
    @@@.@.@.@@
    @@@@@.@.@@
    @.@@@@..@.
    @@.@@@@.@@
    .@@@@@@@.@
    .@.@.@.@@@
    @.@@@.@@@@
    .@@@@@@@@.
    @.@.@@@.@.
    """

  @Test func part1() async throws {
    #expect(Day04.part1(Day04.parseInput(input)) == 13)
  }

  @Test func part2() async throws {
    #expect(Day04.part2(Day04.parseInput(input)) == 0)
  }
}
