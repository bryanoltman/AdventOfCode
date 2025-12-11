import Testing

@testable import AdventOfCode

struct Day05Tests {
  let input = """
    3-5
    10-14
    16-20
    12-18

    1
    5
    8
    11
    17
    32
    """

  @Test func part1() async throws {
    #expect(Day05.part1(Day05.parseInput(input)) == 3)
  }

  @Test func part2() async throws {
    #expect(Day05.part2(Day05.parseInput(input)) == 14)
  }
}
