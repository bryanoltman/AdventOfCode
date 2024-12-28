struct Day21: AdventDay {
  init(data: String) {
    self.data = data
    codes =
      data
      .trimmingCharacters(in: .whitespacesAndNewlines)
      .split(separator: "\n")
      .map { String($0) }

    fullKeypad = Grid(
      string: """
        789
        456
        123
        x0A
        """,
      itemConverter: { String($0) }
    )

    directionKeypad = Grid(
      string: """
        x^A
        <v>
        """,
      itemConverter: { String($0) })
  }

  var data: String

  let codes: [String]

  let fullKeypad: Grid<String>
  let directionKeypad: Grid<String>

  // Full Keypad:
  //  +---+---+---+
  //  | 7 | 8 | 9 |
  //  +---+---+---+
  //  | 4 | 5 | 6 |
  //  +---+---+---+
  //  | 1 | 2 | 3 |
  //  +---+---+---+
  //      | 0 | A |
  //      +---+---+

  // Directional Keypad (starts pointed at "A"):
  //     +---+---+
  //     | ^ | A |
  // +---+---+---+
  // | < | v | > |
  // +---+---+---+

  func part1() -> Int {
    return 0
  }

  func part2() -> Int {
    return 0
  }
}
