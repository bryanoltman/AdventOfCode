import AdventOfCode
import Foundation

let bundle = Bundle(for: Day01.self)
let file = bundle.url(forResource: "03", withExtension: "txt")!
let rawInput = try! String(contentsOf: file, encoding: .utf8)
let input = Day03.parseInput(rawInput)

print("part 1: \(Day03.part1(input))")
print("part 2: \(Day03.part2(input))")
