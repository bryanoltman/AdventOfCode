struct Day15: AdventDay {
  init(data: String) {
    self.data = data

    let parts = data.split(separator: "\n\n")

    self.grid = Grid(string: String(parts[0]), itemConverter: { $0 })
    let directionMap = [
      "<": Point.left,
      ">": Point.right,
      "^": Point.up,
      "v": Point.down,
    ]
    self.directions = parts[1]
      .replacing("\n", with: "")
      .split(separator: "")
      .map { c in
        directionMap[String(c)]!
      }
  }

  var data: String
  let grid: Grid<String>
  let directions: [Point]

  func scoreBoard(grid: Grid<String>) -> Int {
    grid
      .filter { $0 == "O" }
      .map { $0.x + (100 * $0.y) }
      .reduce(0, +)
  }

  func boxSwapPoint(boxPoint: Point, direction: Point, grid: Grid<String>)
    -> Point?
  {
    var boxTargetPoint = boxPoint
    while true {
      let nextSpot = grid.at(point: boxTargetPoint)
      if nextSpot == "." {
        return boxTargetPoint
      } else if nextSpot == "O" {
        boxTargetPoint = boxTargetPoint + direction
      } else {
        return nil
      }
    }
  }

  func moveDirection(_ direction: Point, grid startingGrid: Grid<String>)
    -> Grid<String>
  {
    var grid = startingGrid
    let robotPoint = grid.findFirst(item: "@")!
    let nextPoint = robotPoint + direction
    let nextSpot = grid.at(point: nextPoint)
    if nextSpot == "." {
      grid.swap(robotPoint, nextPoint)
    } else if nextSpot == "O" {
      // Where we will be moving the box to
      if let boxSwap = boxSwapPoint(
        boxPoint: nextPoint,
        direction: direction,
        grid: grid
      ) {
        grid.swap(nextPoint, boxSwap)
        grid.swap(nextPoint, robotPoint)
      }
    }

    return grid
  }

  func part1() -> Int {
    var currentGrid = self.grid
    for d in directions {
      currentGrid = moveDirection(d, grid: currentGrid)
    }

    return scoreBoard(grid: currentGrid)
  }

  func transformMapForPart2(_ grid: Grid<String>) -> Grid<String> {
    var newItems = [[String]]()

    for row in grid.items {
      var newRow = [String]()
      //      If the tile is #, the new map contains ## instead.
      //      If the tile is O, the new map contains [] instead.
      //      If the tile is ., the new map contains .. instead.
      //      If the tile is @, the new map contains @. instead.
      for item in row {
        if item == "#" {
          newRow.append("##")
        } else if item == "O" {
          newRow.append("[]")
        } else if item == "." {
          newRow.append("..")
        } else if item == "@" {
          newRow.append("@.")
        }
      }
      newItems.append(newRow)
    }

    return Grid(items: newItems)
  }

  func part2() -> Int {
    var updatedMap = transformMapForPart2(grid)
    updatedMap.print()
    return 0
  }
}
