struct Region {
  let id: String
  let points: Set<Point>
}

struct Day12: AdventDay {
  init(data: String) {
    self.data = data
    self.grid = Grid(
      string: data,
      itemConverter: {
        $0
      }
    )
  }

  var data: String

  let grid: Grid<String>

  func getRegions(grid: Grid<String>) -> [Region] {
    var unvisitedPoints = Set(grid.points)
    var seenPoints = Set<Point>()
    var regions: [Region] = []
    while !unvisitedPoints.isEmpty {
      let startingPoint = unvisitedPoints.removeFirst()
      if seenPoints.contains(startingPoint) {
        continue
      }

      let newRegionId = grid.at(point: startingPoint)

      var toVisit = [startingPoint]
      var regionPoints = Set<Point>()
      while !toVisit.isEmpty {
        let currentPoint = toVisit.removeFirst()
        if seenPoints.contains(currentPoint) {
          continue
        }
        seenPoints.insert(currentPoint)
        unvisitedPoints.remove(currentPoint)
        regionPoints.insert(currentPoint)
        let neighborsInPlot = grid.neighbors(point: currentPoint)
          .filter {
            grid.at(point: $0) == newRegionId && !seenPoints.contains($0)
          }
        toVisit.append(contentsOf: neighborsInPlot)
      }

      regions.append(Region(id: newRegionId, points: regionPoints))
    }

    return regions
  }

  func perimeter(points: Set<Point>) -> Int {
    var perimeter = 0
    for point in points {
      let neighbors = [
        Point(x: point.x - 1, y: point.y),
        Point(x: point.x + 1, y: point.y),
        Point(x: point.x, y: point.y - 1),
        Point(x: point.x, y: point.y + 1),
      ]

      let numPresentNeighbors = neighbors.filter { points.contains($0) }.count
      // Sides without neighbors add to perimeter
      perimeter += 4 - numPresentNeighbors
    }

    return perimeter
  }

  func area(points: Set<Point>) -> Int {
    points.count
  }

  func part1() -> Int {
    let regions = getRegions(grid: grid)
    return regions.map { perimeter(points: $0.points) * area(points: $0.points) }
      .reduce(0, +)
  }

  func numSides(points: Set<Point>) -> Int {
    return 0
  }

  func part2() -> Int {
    let regions = getRegions(grid: grid)
    return regions.map { numSides(points: $0.points) * area(points: $0.points) }
      .reduce(0, +)
  }
}
