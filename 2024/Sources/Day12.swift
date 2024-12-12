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
      })
  }

  var data: String

  let grid: Grid<String>

  func getRegions(grid: Grid<String>) -> [Region] {
    var unvisitedPoints = Set(grid.points)
    var regions: [Region] = []
    while !unvisitedPoints.isEmpty {
      let startingPoint = unvisitedPoints.removeFirst()
      let newRegionId = grid.at(point: startingPoint)
      var toVisit = [startingPoint]
      var regionPoints = Set<Point>()
      while !toVisit.isEmpty {
        let currentPoint = toVisit.removeFirst()
        unvisitedPoints.remove(currentPoint)
        regionPoints.insert(currentPoint)
        let neighborsInPlot = grid.neighbors(point: currentPoint)
          .filter {
            grid.at(point: $0) == newRegionId && unvisitedPoints.contains($0)
          }
        toVisit.append(contentsOf: neighborsInPlot)
      }

      regions.append(Region(id: newRegionId, points: regionPoints))
    }

    return regions
  }

  func part1() -> Int {
    let regions = getRegions(grid: grid)
    return 0
  }

  func part2() -> Int {
    return 0
  }
}
