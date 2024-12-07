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

  func canSumToTotal(inputRow row: Input.Row) -> Bool {
    // We abuse Input.row to maintain a running total and remaining numbers
    var totalingRows = [row]
    var completedRows: [Input.Row] = []
    while !totalingRows.isEmpty {
      let current = totalingRows.removeFirst()
      if isRowDone(row: current) {
        completedRows.append(current)
        continue
      }

      let remainingNumbers = current.numbers.dropFirst(2)
      let addRowNumbers =
        [current.numbers[0] + current.numbers[1]] + remainingNumbers
      let multRowNumbers =
        [current.numbers[0] * current.numbers[1]] + remainingNumbers
      totalingRows
        .append(Input.Row(total: current.total, numbers: addRowNumbers))
      totalingRows
        .append(Input.Row(total: current.total, numbers: multRowNumbers))
    }

    return completedRows.contains { row in
      row.total == row.numbers[0]
    }
  }

  func part1() -> Int {
    return input.rows.filter { canSumToTotal(inputRow: $0) }.map(\.total)
      .reduce(
        0, +)
  }

  func part2() -> Int { return 0 }
}
