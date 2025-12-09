import AdventOfCode
import Foundation

let bundle = Bundle(for: Day01.self)
let file = bundle.url(forResource: "01", withExtension: "txt")!
let rawInput = try! String(contentsOf: file, encoding: .utf8)
let input = Day01.parseInput(raw: rawInput)

print("part 1: \(Day01.part1(rotations: input))")
print("part 2: \(Day01.part2(rotations: input))")
