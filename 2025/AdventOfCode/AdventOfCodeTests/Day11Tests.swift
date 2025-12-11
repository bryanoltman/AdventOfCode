import Testing

@testable import AdventOfCode

struct Day11Tests {
  let inputPart1 =
    """
    you: bbb ccc
    bbb: ddd eee
    ccc: ddd eee fff
    ddd: ggg
    eee: out
    fff: out
    ggg: out
    hhh: ccc fff iii
    iii: out
    """

  let inputPart2 = """
    svr: aaa bbb
    aaa: fft
    fft: ccc
    bbb: tty
    tty: ccc
    ccc: ddd eee
    ddd: hub
    hub: fff
    eee: dac
    dac: fff
    fff: ggg hhh
    ggg: out
    hhh: out
    """

  @Test func part1() async throws {
    #expect(Day11.part1(map: Day11.parseInput(raw: inputPart1)) == 5)
  }

  @Test func part2() async throws {
    #expect(Day11.part2(map: Day11.parseInput(raw: inputPart2)) == 2)
  }
}
