import Foundation

public class Day02 {
  public struct Range {
    let beg: Int
    let end: Int
  }

  public static func parseInput(raw: String) -> [Range] {
    return raw.split(separator: ",")
      .map { rangeStr in
        let parts = rangeStr.split(separator: "-")
        return Range(beg: Int(parts[0])!, end: Int(parts[1])!)
      }
  }

  static func isIdValid(id: Int) -> Bool {
    let strId = String(id)
    for i in 2..<(strId.count / 2) {
      let chunked = Array(strId).chunked(into: i).map { String($0) }
      for c in chunked {
        if c != chunked.first! {
          continue
        }
      }

      return true
    }

    return false
  }

  public static func part1(ranges: [Range]) -> Int {
    var idsSum = 0
    for range in ranges {
      for id in range.beg...range.end {
        if !isIdValid(id: id) {
          idsSum += id
        }
      }
    }

    return idsSum
  }

  public static func part2(ranges: [Range]) -> Int {
    return 0
  }
}

extension Array {
  func chunked(into size: Int) -> [[Element]] {
    return stride(from: 0, to: count, by: size)
      .map {
        Array(self[$0..<Swift.min($0 + size, count)])
      }
  }
}
