struct ScoredPath: Comparable {
  let score: Int
  let direction: Point
  let path: [Point]

  static func < (lhs: ScoredPath, rhs: ScoredPath) -> Bool {
    return lhs.score < rhs.score
  }
}

struct DirectionPoint: Hashable {
  let direction: Point
  let point: Point
}

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
    var heap = Heap<ScoredPath>()
    heap.insert(ScoredPath(score: 0, direction: Point.right, path: [startPoint]))
    var visited = Set<DirectionPoint>()
    while !heap.isEmpty {
      guard let path = heap.popMin() else {
        return Int.max
      }

      let currentPoint = path.path.last!
      let currentScore = path.score
      let currentDirection = path.direction
      let currentDirectionPoint = DirectionPoint(direction: currentDirection, point: currentPoint)

      if visited.contains(currentDirectionPoint) {
        continue
      }

      visited.insert(currentDirectionPoint)

      if currentPoint == endPoint {
        return currentScore
      }

      for neighbor in grid.neighbors(point: currentPoint) {
        guard [".", "E", "S"].contains(grid.at(point: neighbor)) else {
          continue
        }

        let direction = currentPoint.direction(to: neighbor)
        guard !visited.contains(DirectionPoint(direction: direction, point: neighbor)) else {
          continue
        }

        let movementCost = 1 + (direction == currentDirection ? 0 : 1000)

        heap.insert(
          ScoredPath(
            score: currentScore + movementCost,
            direction: direction,
            path: path.path + [neighbor]
          )
        )
      }
    }

    return Int.max
  }

  func part1() -> Int {
    findBestPathScore()
  }

  var testScoreOverride: Int?

  func findPathsWithScore(_ score: Int) -> [[Point]] {
    var heap = Heap<ScoredPath>()
    heap.insert(ScoredPath(score: 0, direction: Point.right, path: [startPoint]))
    var ret = [[Point]]()
    while !heap.isEmpty {
      guard let path = heap.popMin() else {
        return []
      }

      let currentPoint = path.path.last!
      let currentScore = path.score
      let currentDirection = path.direction

      if currentPoint == endPoint {
        if currentScore == score {
          ret.append(path.path)
        }
      }

      if currentScore >= score {
        continue
      }

      for neighbor in grid.neighbors(point: currentPoint) {
        guard [".", "E", "S"].contains(grid.at(point: neighbor)) else {
          continue
        }

        let direction = currentPoint.direction(to: neighbor)
        guard !path.path.contains(neighbor) else {
          continue
        }

        let movementCost = 1 + (direction == currentDirection ? 0 : 1000)
        let newScore = currentScore + movementCost
        if newScore <= score {
          heap.insert(
            ScoredPath(
              score: currentScore + movementCost,
              direction: direction,
              path: path.path + [neighbor]
            )
          )
        }
      }
    }

    return ret
  }

  func part2() -> Int {
    let pointsOnPaths = findPathsWithScore(
      // the test override or the answer from part 1
      testScoreOverride ?? 93436
    )
    .flatMap { $0 }

    return Set(pointsOnPaths).count
  }
}
