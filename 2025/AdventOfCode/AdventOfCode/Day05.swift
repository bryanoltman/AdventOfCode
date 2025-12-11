import Foundation

public class Day05 {
  public struct NumRange {
    let beg: Int
    let end: Int
  }

  public struct Input {
    let ranges: [NumRange]
    let nums: [Int]
  }

  public static func parseInput(_ input: String) -> Input {
    let parts = input.split(separator: "\n\n")
    let rangeParts = parts[0]
    let ranges = rangeParts.split(separator: "\n")
      .map { line in
        let nums = line.split(separator: "-")
        return NumRange(beg: Int(nums[0])!, end: Int(nums[1])!)
      }
    let nums = parts[1].split(separator: "\n").map { Int($0)! }
    return Input(ranges: ranges, nums: nums)
  }

  public static func part1(_ input: Input) -> Int {
    return input.nums.count { num in input.ranges.contains { $0.containsNum(num) } }
  }

  public static func part2(_ input: Input) -> Int {
    let sortedRanges = input.ranges.sorted { a, b in
      a.beg < b.beg
    }
    var mergedRanges = [NumRange]()
    var currentRange = sortedRanges.first!
    for range in sortedRanges.dropFirst() {
      if range.beg <= currentRange.end {
        currentRange = NumRange(beg: currentRange.beg, end: max(currentRange.end, range.end))
      }
      else {
        mergedRanges.append(currentRange)
        currentRange = range
      }
    }
    mergedRanges.append(currentRange)

    return mergedRanges.reduce(0) { partialResult, range in
      partialResult + (range.end - range.beg) + 1
    }
  }
}

extension Day05.NumRange {
  func containsNum(_ n: Int) -> Bool {
    return n >= beg && n <= end
  }
}
