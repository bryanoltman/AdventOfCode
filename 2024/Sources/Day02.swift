struct Day02: AdventDay {
  var data: String

  // Splits input data into its component parts and convert from string.
  var entities: [[Int]] {
    data.split(separator: "\n")
      .map {
        $0.split(separator: " ").compactMap { Int($0) }
      }
  }

  func isIncreasingCorrectly(input: [Int]) -> Bool {
    for (index, element) in input.enumerated() {
      if index == input.count - 1 {
        break
      }

      let next = input[index + 1]
      if next - element < 1 || next - element > 3 {
        return false
      }
    }

    return true
  }

  func isDecreasingCorrectly(input: [Int], allowedBadLevels: Int = 0) -> Bool {
    for (index, element) in input.enumerated() {
      if index == input.count - 1 {
        break
      }

      let next = input[index + 1]
      if next - element > -1 || next - element < -3 {
        return false
      }
    }

    return true
  }

  func part1() -> Int {
    return entities.count { line in
      return isIncreasingCorrectly(input: line) || isDecreasingCorrectly(input: line)
    }
  }

  func part2() -> Int {
    return 0
  }
}
