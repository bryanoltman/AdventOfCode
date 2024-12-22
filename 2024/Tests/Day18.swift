import Testing

@testable import AdventOfCode

@Suite("Day 18") struct Day18Tests {
  let input = """
    5,4
    4,2
    4,5
    3,0
    2,1
    6,3
    2,4
    1,5
    0,6
    3,3
    2,6
    5,1
    1,2
    5,5
    2,5
    6,5
    1,4
    0,4
    6,4
    1,1
    6,1
    1,0
    0,5
    1,6
    2,0
    """

  @Test func Part1() {
    var day = Day18(data: input)
    day.numBytesToFall = 12
    #expect(day.part1() == "22")
  }

  @Test func Part2() {
    #expect(Day18(data: input).part2() == "6,1")
  }
}
