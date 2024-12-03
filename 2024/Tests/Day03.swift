import Testing

@testable import AdventOfCode

@Suite("Day 3") struct Day03Tests {
  let part1Input = "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))"
  let part2Input = "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))"

  @Test func Part1() {
    #expect(Day03(data: part1Input).part1() == 161)
  }

  @Test func Part2() {
    #expect(Day03(data: part2Input).part2() == 48)
  }
}
