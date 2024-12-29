import Testing

@testable import AdventOfCode

@Suite("Day 22") struct Day22Tests {
  let inputPart1 = """
    1
    10
    100
    2024
    """

  let inputPart2 = """
    1
    2
    3
    2024
    """

  @Test func Evolve() {
    let day = Day22(data: inputPart1)
    let expected = [
      15_887_950,
      16_495_136,
      527345,
      704524,
      1_553_684,
      12_683_156,
      11_100_544,
      12_249_484,
      7_753_432,
      5_908_254,
    ]
    var num = 123
    for e in expected {
      num = day.evolve(num)
      #expect(num == e)
    }
  }

  @Test func Part1() {
    #expect(Day22(data: inputPart1).part1() == 37_327_623)
  }

  @Test func Part2() {
    #expect(Day22(data: inputPart2).part2() == 23)
  }
}
