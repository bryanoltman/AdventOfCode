import Testing

@testable import AdventOfCode

@Suite("Day TODO") struct DayTODOTests {
  let input = """
    """

  @Test func Part1() async throws {
    #expect(DayTODO(data: input).part1() == 0)
  }

  @Test func Part2() async throws {
    #expect(DayTODO(data: input).part2() == 0)
  }
}
