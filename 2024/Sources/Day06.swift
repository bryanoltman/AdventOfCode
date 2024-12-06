struct Day06: AdventDay {
  init(data: String) {
    self.data = data
    grid = Grid(string: data, itemConverter: { s in
      s
    })
  }
  
  var data: String

  let grid: Grid<String>

  func turnRight(point: Point) -> Point {
    if point == Point.up {
      return Point.right
    } else if point == Point.right {
      return Point.down
    } else if point == Point.down {
      return Point.left
    } else if point == Point.left {
      return Point.up
    }

    return Point(x: 0, y: 0)
  }

  func part1() -> Int {
    var visitedPoints = Set<Point>()
    var currentPoint = grid.findFirst(item: "^")!
    var currentDirection = Point.up

    while grid.contains(point: currentPoint) {
      visitedPoints.insert(currentPoint)

      let candidateNextPoint = currentPoint + currentDirection
      if !grid.contains(point: candidateNextPoint) {
        break
      }

      let itemAtNextPosition = grid.at(point: candidateNextPoint)
      if itemAtNextPosition == "#" {
        currentDirection = turnRight(point: currentDirection)
      } else {
        currentPoint = candidateNextPoint
      }
    }

    return visitedPoints.count
  }

  func part2() -> Int {
    return 0
  }
}
