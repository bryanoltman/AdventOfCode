import Testing

@testable import AdventOfCode

@Suite("Day 3") struct Day03Tests {
  let input = "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))"

  @Test func Part1() {
    #expect(Day03(data: input).part1() == 161)
  }

  @Test func Part2() {
    //    #expect(Day03(data: input).part2() == 0)
  }
}
