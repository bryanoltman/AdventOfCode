import Testing

@testable import AdventOfCode

struct Day03Tests {
  let input = """
    987654321111111
    811111111111119
    234234234234278
    818181911112111
    """

  @Test func part1() async throws {
    #expect(Day03.part1(Day03.parseInput(input)) == 357)
  }

  @Test func part2() async throws {
    #expect(Day03.part2(Day03.parseInput(input)) == 3121910778619)
  }
}
