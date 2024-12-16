struct Day15: AdventDay {
  init(data: String) {
    self.data = data

    let parts = data.split(separator: "\n\n")

    self.gridString = String(parts[0])
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
  let gridString: String
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
      }
      else if nextSpot == "O" {
        boxTargetPoint = boxTargetPoint + direction
      }
      else {
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
    }
    else if nextSpot == "O" {
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
    var currentGrid = Grid(string: gridString, itemConverter: { $0 })
    for d in directions {
      currentGrid = moveDirection(d, grid: currentGrid)
    }

    return scoreBoard(grid: currentGrid)
  }

  func boxPointsPart2(boxPoint: Point, grid: Grid<String>) -> [Point] {
    let spotContents = grid.at(point: boxPoint)
    if spotContents == "]" {
      return [boxPoint + Point.left, boxPoint]
    }
    else if spotContents == "[" {
      return [boxPoint, boxPoint + Point.right]
    }

    return []
  }

  func part2BoxesInGroup(boxPoint: Point, direction: Point, grid: Grid<String>) -> [Point] {
    let boxPoints = boxPointsPart2(boxPoint: boxPoint, grid: grid)
    var boxesPoints = boxPoints
    var nextRow = Set<Point>()
    var currentRow = boxPoints
    repeat {
      nextRow = Set<Point>()
      for point in currentRow {
        let pointInDirection = point + direction
        for boxPointInDirection in boxPointsPart2(boxPoint: pointInDirection, grid: grid) {
          if !boxesPoints.contains(boxPointInDirection) {
            nextRow.insert(boxPointInDirection)
          }
        }
      }
      boxesPoints += Array(nextRow)
      currentRow = Array(nextRow)
    }
    while !nextRow.isEmpty

    return boxesPoints
  }

  func canMoveBoxesPart2(boxesPoints: [Point], direction: Point, grid: Grid<String>) -> Bool {
    for p in boxesPoints {
      let directionPoint = p + direction
      let spot = grid.at(point: directionPoint)
      if boxesPoints.contains(directionPoint) {
        continue
      }
      if spot != "." {
        return false
      }
    }

    return true
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
          newRow += ["#", "#"]
        }
        else if item == "O" {
          newRow += ["[", "]"]
        }
        else if item == "." {
          newRow += [".", "."]
        }
        else if item == "@" {
          newRow += ["@", "."]
        }
      }
      newItems.append(newRow)
    }

    return Grid(items: newItems)
  }

  func moveBoxesPart2(_ boxPoints: [Point], direction: Point, grid startingGrid: Grid<String>) -> Grid<
    String
  > {
    var grid = startingGrid
    for point in boxPoints {
      grid.items[point.y][point.x] = "."
    }
    for point in boxPoints {
      let targetPoint = point + direction
      grid.items[targetPoint.y][targetPoint.x] = startingGrid.at(point: point)
    }
    return grid
  }

  func moveDirectionPart2(_ direction: Point, grid startingGrid: Grid<String>) -> Grid<String> {
    var grid = startingGrid
    let robotPoint = grid.findFirst(item: "@")!
    let nextPoint = robotPoint + direction
    let nextSpot = grid.at(point: nextPoint)

    if nextSpot == "." {
      grid.swap(robotPoint, nextPoint)
    }
    else if nextSpot == "[" || nextSpot == "]" {
      let boxPoints = part2BoxesInGroup(boxPoint: nextPoint, direction: direction, grid: grid)
      if canMoveBoxesPart2(boxesPoints: boxPoints, direction: direction, grid: grid) {
        grid = moveBoxesPart2(boxPoints, direction: direction, grid: grid)
        grid.swap(robotPoint, nextPoint)
      }
    }

    return grid
  }

  func scoreBoardPart2(grid: Grid<String>) -> Int {
    grid
      .filter { $0 == "[" }
      .map { $0.x + (100 * $0.y) }
      .reduce(0, +)
  }

  func part2() -> Int {
    let grid = Grid(string: gridString, itemConverter: { $0 })
    var updatedMap = transformMapForPart2(grid)
    for d in directions {
      updatedMap = moveDirectionPart2(d, grid: updatedMap)
    }
    return scoreBoardPart2(grid: updatedMap)
  }
}
