import Foundation

struct Day03: AdventDay {

  var data: String

  let mulRegex = try! NSRegularExpression(pattern: #"mul\((\d+),(\d+)\)"#)

  func part1() -> Int {
    return mulRegex.matches(in: data, range: NSRange(data.startIndex..., in: data))
      .map { match in
        let range1 = Range(match.range(at: 1), in: data)!
        let range2 = Range(match.range(at: 2), in: data)!
        let num1 = Int(String(data[range1]))!
        let num2 = Int(String(data[range2]))!
        return num1 * num2
      }
      .reduce(0, +)
  }

  func part2() -> Int {
    return 0
  }
}
