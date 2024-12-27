struct Day16: AdventDay {
  init(data: String) {
    self.data = data
    self.grid = Grid(
      string: data.trimmingCharacters(in: .whitespacesAndNewlines),
      itemConverter: { String($0) }
    )
  }

  var data: String

  let grid: Grid<String>

  var startPoint: Point {
    grid.findFirst(item: "S")!
  }

  var endPoint: Point {
    grid.findFirst(item: "E")!
  }

  func findBestPathScore() -> Int {
    var openPaths: [(Int, [Point])] = [(0, [startPoint])]
    var closedPaths = [(Int, [Point])]()
    var currentBestScore = Int.max
    var bestPointScores = [Point: Int]()

    while !openPaths.isEmpty {
      let (currentScore, currentPath) = openPaths.popLast()!
      let currentPoint = currentPath.last!

      if bestPointScores[currentPoint, default: Int.max] < currentScore {
        continue
      }

      bestPointScores[currentPoint] = currentScore

      if currentPoint == endPoint {
        closedPaths.append((currentScore, currentPath))
        if currentScore < currentBestScore {
          currentBestScore = currentScore
        }
        continue
      }

      let neighbors = grid.neighbors(point: currentPoint)
        .filter {
          [".", "E", "S"].contains(grid.at(point: $0))
        }
        .filter { !currentPath.contains($0) }
      let currentDirection =
        currentPath.count == 1
        ? Point.right : currentPath[currentPath.count - 2].direction(to: currentPoint)

      for n in neighbors {
        let direction = currentPoint.direction(to: n)
        let movementCost = 1 + (direction == currentDirection ? 0 : 1000)
        openPaths.append((currentScore + movementCost, currentPath + [n]))
      }
    }

    return currentBestScore
  }

  func part1() -> Int {
    findBestPathScore()
  }

  func part2() -> Int {
    return 0
  }
}
