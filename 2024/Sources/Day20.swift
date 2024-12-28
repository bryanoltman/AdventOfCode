struct Day20: AdventDay {
  init(data: String) {
    self.data = data
    grid = Grid(string: data.trimmingCharacters(in: .whitespacesAndNewlines), itemConverter: { $0 })
  }

  var data: String

  let grid: Grid<String>
  
  var startPoint: Point {
    grid.findFirst(item: "S")!
  }

  var endPoint: Point {
    grid.findFirst(item: "E")!
  }

  func part1() -> Int {
    return 0
  }

  func part2() -> Int {
    return 0
  }
}
