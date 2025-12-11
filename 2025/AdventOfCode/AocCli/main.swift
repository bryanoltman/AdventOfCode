import AdventOfCode
import Foundation

let bundle = Bundle(for: Day06.self)
let file = bundle.url(forResource: "06", withExtension: "txt")!
let rawInput = try! String(contentsOf: file, encoding: .utf8)
let input = Day06.parseInput(rawInput)

print("part 1: \(Day06.part1(input))")
print("part 2: \(Day06.part2(input))")
