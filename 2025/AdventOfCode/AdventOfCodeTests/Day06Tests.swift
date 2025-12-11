import Testing

@testable import AdventOfCode

struct Day06Tests {
  let input = """
    123 328  51 64 
     45 64  387 23 
      6 98  215 314
    *   +   *   +  
    """

  @Test func part1() async throws {
    #expect(Day06.part1(Day06.parseInput(input)) == 4277556)
  }

  @Test func part2() async throws {
    #expect(Day06.part2(Day06.parseInput(input)) == 3263827)
  }
}
