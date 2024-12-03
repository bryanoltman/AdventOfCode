import Foundation

struct Day03: AdventDay {

  var data: String

  let doRegex = try! NSRegularExpression(pattern: #"do\(\)"#)
  let dontRegex = try! NSRegularExpression(pattern: #"don't\(\)"#)
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

  enum ControlFlowMatch {
    case start
    case stop
    case mult(Int, Int)
  }

  func part2() -> Int {
    var multiplicationEnabled = true
    let dataRange = NSRange(data.startIndex..., in: data)
    let multMatches = mulRegex.matches(in: data, range: dataRange)
    let doMatches = doRegex.matches(in: data, range: dataRange)
    let dontMatches = dontRegex.matches(in: data, range: dataRange)

    var allMatches = [(Int, ControlFlowMatch)]()
    for match in multMatches {
      let range1 = Range(match.range(at: 1), in: data)!
      let range2 = Range(match.range(at: 2), in: data)!
      let num1 = Int(String(data[range1]))!
      let num2 = Int(String(data[range2]))!
      allMatches.append((match.range.location, .mult(num1, num2)))
    }

    for match in doMatches {
      allMatches.append((match.range.location, .start))
    }

    for match in dontMatches {
      allMatches.append((match.range.location, .stop))
    }

    allMatches.sort { (lhs, rhs) in
      lhs.0 < rhs.0
    }

    var sum = 0
    for match in allMatches.map({ $0.1 })  {
      if case .start = match {
        multiplicationEnabled = true
        continue
      }

      if case .stop = match {
        multiplicationEnabled = false
        continue
      }

      if case .mult(let x, let y) = match {
        guard multiplicationEnabled else { continue }
        sum += x * y
      }
    }

    return sum
  }
}
