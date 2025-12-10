import Testing

@testable import AdventOfCode

struct Day01Tests {
  let input = """
    L68
    L30
    R48
    L5
    R60
    L55
    L1
    L99
    R14
    L82
    """

  @Test func part1() async throws {
    #expect(Day01.part1(rotations: Day01.parseInput(raw: input)) == 3)
  }

  @Test func part2() async throws {
    #expect(Day01.part2(rotations: Day01.parseInput(raw: input)) == 6)
  }
}
