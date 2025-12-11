import Foundation

public class Day03 {
  public static func parseInput(_ input: String) -> [String] {
    return input.split(separator: "\n").map { String($0) }
  }

  static func largestJoltage(bank: String, numBatteries: Int) -> Int {
    let nums = bank.split(separator: "").map { Int($0)! }
    var numToGo = numBatteries
    var numSoFar = ""
    var lastNumIdx = 0
    while numToGo > 0 {
      var nextMax = Int.min
      for i in (lastNumIdx)..<(nums.count - numToGo + 1) {
        let currentNum = nums[i]
        if currentNum > nextMax {
          nextMax = currentNum
          lastNumIdx = i + 1
        }
      }

      numSoFar += String(nextMax)
      numToGo -= 1
    }

    return Int(numSoFar)!
  }

  public static func part1(_ input: [String]) -> Int {
    return input.reduce(0) { partialResult, bank in
      partialResult + largestJoltage(bank: bank, numBatteries: 2)
    }
  }

  public static func part2(_ input: [String]) -> Int {
    return input.reduce(0) { partialResult, bank in
      partialResult + largestJoltage(bank: bank, numBatteries: 12)
    }
  }
}
