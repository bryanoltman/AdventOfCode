import Testing

@testable import AdventOfCode

@Suite("Day 14") struct Day14Tests {
  let input = """
    p=0,4 v=3,-3
    p=6,3 v=-1,-3
    p=10,3 v=-1,2
    p=2,0 v=2,-1
    p=0,0 v=1,3
    p=3,0 v=-2,-2
    p=7,6 v=-1,-3
    p=3,0 v=-1,-2
    p=9,3 v=2,3
    p=7,3 v=-1,2
    p=2,4 v=2,-3
    p=9,5 v=-3,-3
    """

  
  @Test func Part1() async throws {
    let day = Day14(data: input, width: 11, height: 7)
    #expect(day.part1() == 12)
  }

  @Test func Part2() async throws {
    let day = Day14(data: input, width: 11, height: 7)
    #expect(day.part2() == 0)
  }
}
