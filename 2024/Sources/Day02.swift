struct Day02: AdventDay {
  var data: String

  // Splits input data into its component parts and convert from string.
  var entities: [[Int]] {
    data.split(separator: "\n")
      .map {
        $0.split(separator: " ").compactMap { Int($0) }
      }
  }

  func checkLevels(levels: [Int], increasing: Bool) -> Bool {
    for i in 0..<levels.count - 1 {
      let current = levels[i]
      let next = levels[i + 1]
      let diff = next - current
      if increasing && !(1..<4).contains(diff) {
        return false
      }

      if !increasing && !(-3..<0).contains(diff) {
        return false
      }
    }

    return true
  }

  func isSafe(levels: [Int]) -> Bool {
    return checkLevels(levels: levels, increasing: true)
      || checkLevels(levels: levels, increasing: false)
  }

  func part1() -> Int {
    return entities.count(where: isSafe)
  }

  func part2() -> Int {
    return 0
  }
}
