struct Day02: AdventDay {
  var data: String

  // Splits input data into its component parts and convert from string.
  var entities: [[Int]] {
    data.split(separator: "\n")
      .map {
        $0.split(separator: " ").compactMap { Int($0) }
      }
  }

  func checkLevels(levels: [Int], increasing: Bool, canSplit: Bool = false) -> Bool {
    for i in 0..<levels.count - 1 {
      let current = levels[i]
      let next = levels[i + 1]
      let diff = next - current
      if increasing && !(1..<4).contains(diff) {
        if canSplit {
          var copy1 = levels
          copy1.remove(at: i)
          var copy2 = levels
          copy2.remove(at: i + 1)
          var copy3 = levels
          if i > 0 {
            copy3.remove(at: i - 1)
          }
          return checkLevels(levels: copy1, increasing: true)
            || checkLevels(levels: copy2, increasing: true)
            || checkLevels(levels: copy3, increasing: true)
        }
        else {
          return false
        }
      }

      if !increasing && !(-3..<0).contains(diff) {
        if canSplit {
          var copy1 = levels
          copy1.remove(at: i)
          var copy2 = levels
          copy2.remove(at: i + 1)
          var copy3 = levels
          if i > 0 {
            copy3.remove(at: i - 1)
          }
          return checkLevels(levels: copy1, increasing: false)
            || checkLevels(levels: copy2, increasing: false)
            || checkLevels(levels: copy3, increasing: false)
        }
        else {
          return false
        }
      }
    }

    return true
  }

  func isSafe(levels: [Int], canSplit: Bool = false) -> Bool {
    return checkLevels(levels: levels, increasing: true, canSplit: canSplit)
      || checkLevels(levels: levels, increasing: false, canSplit: canSplit)
  }

  func part1() -> Int {
    return entities.count { row in
      isSafe(levels: row)
    }
  }

  func part2() -> Int {
    return entities.count { row in
      isSafe(levels: row, canSplit: true)
    }
  }
}
