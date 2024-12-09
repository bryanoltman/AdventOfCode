import Testing

@testable import AdventOfCode

@Suite("Day 8") struct Day08Tests {

  let input = """
    ............
    ........0...
    .....0......
    .......0....
    ....0.......
    ......A.....
    ............
    ............
    ........A...
    .........A..
    ............
    ............
    """

  @Test func Antinodes() {
    let day = Day08(data: input)
    let a1 = Point(x: 8, y: 8)
    let a2 = Point(x: 9, y: 9)
    #expect(
      day.getAntinodesPart1(a: a1, b: a2) == [
        Point(x: 7, y: 7), Point(x: 10, y: 10),
      ]
    )
    #expect(
      day.getAntinodesPart1(a: a2, b: a1) == [
        Point(x: 10, y: 10), Point(x: 7, y: 7),
      ]
    )

    let b1 = Point(x: 8, y: 1)
    let b2 = Point(x: 5, y: 2)
    #expect(
      day.getAntinodesPart1(a: b1, b: b2) == [
        Point(x: 11, y: 0), Point(x: 2, y: 3),
      ]
    )
  }

  @Test func Part1() {
    #expect(Day08(data: input).part1() == 14)
  }

  @Test func Part2() {
    #expect(Day08(data: input).part2() == 34)
  }
}
