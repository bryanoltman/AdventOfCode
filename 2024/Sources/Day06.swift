struct Day06: AdventDay {
  init(data: String) {
    self.data = data
    grid = Grid(
      string: data,
      itemConverter: { s in
        s
      }
    )
  }

  var data: String

  let grid: Grid<String>

  func turnRight(point: Point) -> Point {
    if point == Point.up {
      return Point.right
    }
    else if point == Point.right {
      return Point.down
    }
    else if point == Point.down {
      return Point.left
    }
    else if point == Point.left {
      return Point.up
    }

    return Point(x: 0, y: 0)
  }

  func getPath(grid: Grid<String>) -> Set<PointDirection> {
    var history = Set<PointDirection>()
    var currentPoint = grid.findFirst(item: "^")!
    var currentDirection = Point.up
    while grid.contains(point: currentPoint) {
      history.insert(PointDirection(point: currentPoint, direction: currentDirection))

      let candidateNextPoint = currentPoint + currentDirection
      if !grid.contains(point: candidateNextPoint) {
        break
      }

      let itemAtNextPosition = grid.at(point: candidateNextPoint)
      if itemAtNextPosition == "#" {
        currentDirection = turnRight(point: currentDirection)
      }
      else {
        currentPoint = candidateNextPoint
      }
    }

    return history
  }

  func part1() -> Int {
    return Set(getPath(grid: grid).map { $0.point }).count
  }

  func isLoop(grid: Grid<String>) -> Bool {
    var history = Set<PointDirection>()
    var currentPoint = grid.findFirst(item: "^")!
    var currentDirection = Point.up
    while grid.contains(point: currentPoint) {
      let currentPd = PointDirection(point: currentPoint, direction: currentDirection)
      if history.contains(currentPd) {
        return true
      }
      history.insert(PointDirection(point: currentPoint, direction: currentDirection))

      let candidateNextPoint = currentPoint + currentDirection
      if !grid.contains(point: candidateNextPoint) {
        break
      }

      let itemAtNextPosition = grid.at(point: candidateNextPoint)
      if itemAtNextPosition == "#" {
        currentDirection = turnRight(point: currentDirection)
      }
      else {
        currentPoint = candidateNextPoint
      }
    }

    return false
  }

  func part2() -> Int {
    let defaultPath = getPath(grid: grid)
    var loopCount = 0

    for point in Set(defaultPath.map({ $0.point })) {
      if grid.at(point: point) != "." {
        continue
      }

      var itemsCopy = grid.items
      itemsCopy[point.y][point.x] = "#"
      let newGrid = Grid(items: itemsCopy)

      if isLoop(grid: newGrid) {
        loopCount += 1
      }
    }

    return loopCount
  }
}

class PointDirection: Hashable, Equatable {
  static func == (lhs: PointDirection, rhs: PointDirection) -> Bool {
    lhs.point == rhs.point && lhs.direction == rhs.direction
  }

  func hash(into hasher: inout Hasher) {
    hasher.combine(point)
    hasher.combine(direction)
  }

  init(point: Point, direction: Point) {
    self.point = point
    self.direction = direction
  }

  let point: Point
  let direction: Point
}
