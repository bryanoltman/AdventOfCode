import AdventOfCode
import Foundation

let bundle = Bundle(for: Day01.self)
let file = bundle.url(forResource: "04", withExtension: "txt")!
let rawInput = try! String(contentsOf: file, encoding: .utf8)
let input = Day04.parseInput(rawInput)

print("part 1: \(Day04.part1(input))")
print("part 2: \(Day04.part2(input))")
