import AdventOfCode
import Foundation

let bundle = Bundle(for: Day05.self)
let file = bundle.url(forResource: "05", withExtension: "txt")!
let rawInput = try! String(contentsOf: file, encoding: .utf8)
let input = Day05.parseInput(rawInput)

print("part 1: \(Day05.part1(input))")
print("part 2: \(Day05.part2(input))")
