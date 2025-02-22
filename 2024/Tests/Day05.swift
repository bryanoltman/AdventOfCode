import Testing

@testable import AdventOfCode

@Suite("Day 5") struct Day05Tests {

  let input = """
    47|53
    97|13
    97|61
    97|47
    75|29
    61|13
    75|53
    29|13
    97|29
    53|29
    61|53
    97|53
    61|29
    47|13
    75|47
    97|75
    47|61
    75|61
    47|29
    75|13
    53|13

    75,47,61,53,29
    97,61,53,29,13
    75,29,13
    75,97,47,61,53
    61,13,29
    97,13,75,29,47
    """

  @Test func ParsesInput() async throws {
    let day5 = Day05(data: input)
    #expect(
      day5.updates == [
        [75, 47, 61, 53, 29],
        [97, 61, 53, 29, 13],
        [75, 29, 13],
        [75, 97, 47, 61, 53],
        [61, 13, 29],
        [97, 13, 75, 29, 47],
      ]
    )
  }

  @Test func Part1() async throws {
    #expect(Day05(data: input).part1() == 143)
  }

  @Test func Part2() async throws {
    #expect(Day05(data: input).part2() == 123)
  }
}
