struct Operations: OptionSet {
  let rawValue: Int

  static let addition = Operations(rawValue: 1 << 0)
  static let multiplication = Operations(rawValue: 1 << 1)
  static let concatenation = Operations(rawValue: 1 << 2)
}

struct Day07: AdventDay {
  struct Input {
    let rows: [Row]

    struct Row {
      let total: Int
      let numbers: [Int]
    }
  }

  init(data: String) {
    self.data = data
    var rows = [Input.Row]()
    for rowString in data.split(separator: "\n") {
      let allNumbers = rowString.split(separator: ":")
      let total = Int(allNumbers[0])!
      let row = allNumbers.dropFirst().map { $0.split(separator: " ") }
        .flatMap { $0 }
        .map { Int($0)! }
      let inputRow = Input.Row(total: total, numbers: row)
      rows.append(inputRow)
    }

    self.input = .init(rows: rows)
  }

  var data: String

  let input: Input

  func isRowDone(row: Input.Row) -> Bool {
    row.numbers.count == 1
  }

  func isCandidate(inputRow row: Input.Row, allowedOperations: Operations)
    -> Bool
  {
    // We abuse Input.row to maintain a running total and remaining numbers
    var totalingRows = [row]
    var completedRows: [Input.Row] = []
    while !totalingRows.isEmpty {
      let current = totalingRows.removeFirst()

      if current.total < current.numbers[0] {
        continue
      }

      var adjustedNumbers = [Int]()
      if allowedOperations.contains(.addition) {
        adjustedNumbers.append(current.numbers[0] + current.numbers[1])
      }

      if allowedOperations.contains(.multiplication) {
        adjustedNumbers.append(current.numbers[0] * current.numbers[1])
      }

      if allowedOperations.contains(.concatenation) {
        adjustedNumbers.append(
          Int("\(current.numbers[0])\(current.numbers[1])")!)
      }
      let remainingNumbers = current.numbers.dropFirst(2)

      for num in adjustedNumbers {
        let adjustedRow = Input.Row(
          total: row.total, numbers: [num] + remainingNumbers)

        if isRowDone(row: adjustedRow) {
          completedRows.append(adjustedRow)
        } else {
          totalingRows.append(adjustedRow)
        }
      }
    }

    return completedRows.contains { row in
      row.total == row.numbers[0]
    }
  }

  func part1() -> Int {
    return input.rows
      .filter {
        isCandidate(
          inputRow: $0, allowedOperations: [.addition, .multiplication])
      }
      .map(\.total)
      .reduce(0, +)
  }

  func part2() -> Int {
    return input.rows
      .filter {
        isCandidate(
          inputRow: $0,
          allowedOperations: [
            .addition,
            .multiplication,
            .concatenation,
          ]
        )
      }
      .map(\.total)
      .reduce(0, +)
  }
}
