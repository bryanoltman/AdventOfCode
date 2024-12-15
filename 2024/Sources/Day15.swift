struct Day15: AdventDay {
  init(data: String) {
    self.data = data

    let parts = data.split(separator: "\n\n")

    self.grid = Grid(string: String(parts[0]), itemConverter: { $0 })
    let directionMap = [
      "<": Point.left,
      ">": Point.right,
      "^": Point.up,
      "v": Point.down
    ]
    self.directions = parts[1]
      .replacing("\n", with: "")
      .split(separator: "")
      .map({ c in
      directionMap[String(c)]!
    })
  }

  var data: String
  let grid: Grid<String>
  let directions: [Point]

  func part1() -> Int {
    return 0
  }

  func part2() -> Int {
    return 0
  }
}
