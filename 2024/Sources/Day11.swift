struct Day11: AdventDay {
  var data: String

  var stones: [Int] {
    data.trimmingCharacters(in: .whitespacesAndNewlines).split(separator: " ").map { Int($0)! }
  }

  func hasEvenNumberOfDigits(_ number: Int) -> Bool {
    var count = 0
    var num = abs(number)

    while num > 0 {
      count += 1
      num /= 10
    }

    return count % 2 == 0
  }

  func blink(stoneCounts originalCounts: [Int: Int]) -> [Int: Int] {
    var newCounts = [Int: Int]()
    for (stone, count) in originalCounts {
      let stoneStr = String(stone)
      if stone == 0 {
        // Zeroes become ones
        newCounts[1, default: 0] += count
      }
      else if stoneStr.count % 2 == 0 {
        // Stones with an even number of digits are replaced by two stones
        // 1234 -> 12 34
        let middleIndex = stoneStr.index(stoneStr.startIndex, offsetBy: stoneStr.count / 2)
        let firstHalf = String(stoneStr[stoneStr.startIndex..<middleIndex])
        let secondHalf = String(stoneStr[middleIndex..<stoneStr.endIndex])
        newCounts[Int(firstHalf)!, default: 0] += count
        newCounts[Int(secondHalf)!, default: 0] += count
      }
      else {
        // the old stone's number multiplied by 2024 is engraved on the new stone
        newCounts[stone * 2024, default: 0] += count
      }
    }

    return newCounts
  }

  func part1() -> Int {
    var stoneCounts = [Int: Int]()
    for stone in stones {
      stoneCounts[stone, default: 0] += 1
    }

    for _ in 0..<25 {
      stoneCounts = blink(stoneCounts: stoneCounts)
    }

    return stoneCounts.values.reduce(0, +)
  }

  func part2() -> Int {
    var stoneCounts = [Int: Int]()
    for stone in stones {
      stoneCounts[stone, default: 0] += 1
    }

    for _ in 0..<75 {
      stoneCounts = blink(stoneCounts: stoneCounts)
    }

    return stoneCounts.values.reduce(0, +)
  }
}
