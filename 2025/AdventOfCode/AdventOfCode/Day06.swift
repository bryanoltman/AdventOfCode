import Foundation

public class Day06 {
  public struct Column {
    let nums: [String]
    let op: (Int, Int) -> Int
  }

  public struct Input {
    let columns: [Column]
  }

  public static func parseInput(_ input: String) -> Input {
    let lines = input.split(separator: "\n")
    let numberLines = lines.dropLast()
      .map {
        Array($0)
      }
    let opLine = Array(lines.last!)
    let longestLineLength = numberLines.map { $0.count }.max()!
    var columns = [Column]()
    var currentIdx = 0
    while currentIdx < longestLineLength {
      var nextIdx = currentIdx + 1
      let opStr = opLine[currentIdx]
      let op: (Int, Int) -> Int = {
        if opStr == "*" {
          return (*)
        }
        else {
          return (+)
        }
      }()

      while nextIdx < opLine.count && opLine[nextIdx] == " " {
        nextIdx += 1
      }

      if nextIdx == opLine.count {
        nextIdx += 1
      }

      let nums = numberLines.map { line in
        let numStr = line[currentIdx..<(nextIdx - 1)]
        return numStr.map { String($0) }.joined()
      }

      columns.append(Column(nums: nums, op: op))
      currentIdx = nextIdx
    }

    return Input(columns: columns)
  }

  public static func part1(_ input: Input) -> Int {
    var sum = 0
    for column in input.columns {
      let num = Int(column.nums.first!.trimmingCharacters(in: .whitespacesAndNewlines))!
      sum += column.nums.dropFirst()
        .reduce(
          num,
          { partialResult, str in
            column.op(partialResult, Int(str.trimmingCharacters(in: .whitespacesAndNewlines))!)
          }
        )
    }

    return sum
  }

  public static func part2(_ input: Input) -> Int {
    var sum = 0

    for column in input.columns {
      let strLength = column.nums.first!.count
      var numStrs = Array(repeating: "", count: column.nums.count)
      for i in (0..<strLength).reversed() {
        for num in column.nums {
          numStrs[i] += num.split(separator: "")[i]
        }
      }

      numStrs = numStrs.filter { !$0.isEmpty }

      let num = Int(numStrs.first!.trimmingCharacters(in: .whitespacesAndNewlines))!
      sum += numStrs.dropFirst()
        .reduce(
          num,
          { partialResult, str in
            column.op(partialResult, Int(str.trimmingCharacters(in: .whitespacesAndNewlines))!)
          }
        )
    }

    return sum
  }
}
