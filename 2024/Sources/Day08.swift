struct Day08: AdventDay {
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

  /// Maps antenna frequencies to their points on the grid
  func antennaMap(grid: Grid<String>) -> [String: Set<Point>] {
    var map = [String: Set<Point>]()
    for point in grid.points {
      let item = grid.at(point: point)
      if item == "." {
        continue
      }

      map[item, default: Set<Point>()].insert(point)
    }

    return map
  }

  func getAntinodesPart1(a: Point, b: Point) -> [Point] {
    let slope = a - b

    var antinodes = [Point]()
    var candidate = a
    while grid.contains(point: candidate) {
      candidate = candidate + slope
      let aDist = candidate.manhattanDistance(from: a)
      let bDist = candidate.manhattanDistance(from: b)
      if bDist * 2 == aDist || aDist * 2 == bDist {
        antinodes.append(candidate)
      }
    }
    candidate = a
    while grid.contains(point: candidate) {
      candidate = candidate - slope
      let aDist = candidate.manhattanDistance(from: a)
      let bDist = candidate.manhattanDistance(from: b)
      if bDist * 2 == aDist || aDist * 2 == bDist {
        antinodes.append(candidate)
      }
    }
    return antinodes
  }

  /// From AOC:
  /// an antinode occurs at any point that is perfectly in line with two antennas of the
  /// same frequency - but only when one of the antennas is twice as far away as the other.
  /// This means that for any pair of antennas with the same frequency, there are two antinodes,
  /// one on either side of them.
  func getAntinodesPart1(grid: Grid<String>) -> Set<Point> {
    var antinodes = Set<Point>()
    for (_, points) in antennaMap(grid: grid) {
      let listPoints = Array(points)
      for i in 0..<listPoints.count {
        for j in (i + 1)..<listPoints.count {
          let a = listPoints[i]
          let b = listPoints[j]
          let currentAntinodes = getAntinodesPart1(a: a, b: b)
          for currentAntinode in currentAntinodes {
            guard grid.contains(point: currentAntinode) else {
              continue
            }

            antinodes.insert(currentAntinode)
          }
        }
      }
    }

    return antinodes
  }

  func part1() -> Int {
    getAntinodesPart1(grid: grid).count
  }

  func getAntinodesPart2(a: Point, b: Point) -> Set<Point> {
    let slope = a - b

    var antinodes = Set<Point>()
    var candidate = a
    while grid.contains(point: candidate) {
      antinodes.insert(candidate)
      candidate = candidate + slope
    }
    candidate = a
    while grid.contains(point: candidate) {
      antinodes.insert(candidate)
      candidate = candidate - slope
    }
    return antinodes
  }

  func getAntinodesPart2(grid: Grid<String>) -> Set<Point> {
    var antinodes = Set<Point>()
    for (_, points) in antennaMap(grid: grid) {
      let listPoints = Array(points)
      for i in 0..<listPoints.count {
        for j in (i + 1)..<listPoints.count {
          let a = listPoints[i]
          let b = listPoints[j]
          let currentAntinodes = getAntinodesPart2(a: a, b: b)
          for currentAntinode in currentAntinodes {
            guard grid.contains(point: currentAntinode) else {
              continue
            }

            antinodes.insert(currentAntinode)
          }
        }
      }
    }

    return antinodes
  }

  func part2() -> Int {
    getAntinodesPart2(grid: grid).count
  }
}
