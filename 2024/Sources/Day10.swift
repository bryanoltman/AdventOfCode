struct Day10: AdventDay {
  init(data: String) {
    self.data = data

    self.grid = Grid(
      string: data,
      itemConverter: {
        Int($0) ?? -10
      }
    )
  }

  var data: String

  let grid: Grid<Int>

  var trailheads: [Point] {
    grid.points.filter {
      grid.at(point: $0) == 0
    }
  }

  // Number of 9s that are visitable from this trailhead
  func scoreTrailheadPart1(trailhead: Point) -> Int {
    var visitedPoints = Set<Point>()
    var pointsToVisit = Set<Point>()
    pointsToVisit.insert(trailhead)
    var nineHeightCount = 0
    while !pointsToVisit.isEmpty {
      let currentPoint = pointsToVisit.removeFirst()
      visitedPoints.insert(currentPoint)
      let currentHeight = grid.at(point: currentPoint)
      if currentHeight == 9 {
        nineHeightCount += 1
      }

      let toVisit = grid.neighbors(point: currentPoint)
        .filter { !visitedPoints.contains($0) }
        .filter {
          grid.at(point: $0) - currentHeight == 1
        }

      for p in toVisit {
        pointsToVisit.insert(p)
      }
    }

    return nineHeightCount
  }

  func part1() -> Int {
    trailheads.map(scoreTrailheadPart1(trailhead:))
      .reduce(0, +)
  }

  // Number of distinct ways to get to 9s from this trailhead
  func scoreTrailheadPart2(trailhead: Point) -> Int {
    var openPaths = [[Point]]()
    var completedPaths = [[Point]]()

    openPaths.append([trailhead])

    while !openPaths.isEmpty {
      let currentPath = openPaths.removeFirst()
      let currentPoint = currentPath.last!
      let currentHeight = grid.at(point: currentPoint)
      if currentHeight == 9 {
        completedPaths.append(currentPath)
        continue
      }

      let toVisit = grid.neighbors(point: currentPoint)
        .filter { !currentPath.contains($0) }
        .filter {
          grid.at(point: $0) - currentHeight == 1
        }
      for neighbor in toVisit {
        openPaths.append(currentPath + [neighbor])
      }
    }

    return completedPaths.count
  }

  func part2() -> Int {
    trailheads.map(scoreTrailheadPart2(trailhead:))
      .reduce(0, +)
  }
}
