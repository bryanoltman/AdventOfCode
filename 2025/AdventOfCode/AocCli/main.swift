import AdventOfCode
import Foundation

let bundle = Bundle(for: Day01.self)
let file = bundle.url(forResource: "11", withExtension: "txt")!
let rawInput = try! String(contentsOf: file, encoding: .utf8)
let input = Day11.parseInput(raw: rawInput)

print("part 1: \(Day11.part1(map: input))")
print("part 2: \(Day11.part2(map: input))")
