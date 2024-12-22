import Foundation

struct Day18: AdventDay {
  init(data: String) {
    self.data = data
    coords = data.trimmingCharacters(in: .whitespacesAndNewlines)
      .split(separator: "\n")
      .map { line in
        let parts = line.split(separator: ",")
        return Point(x: Int(parts[0])!, y: Int(parts[1])!)
      }

  }

  var data: String

  let coords: [Point]

  var numBytesToFall = 1024

  func gridAfterFallenBytes(numBytes: Int) -> Grid<String> {
    let tmpCoords = coords[..<numBytes]
    let maxX = coords.map { $0.x }.max()!
    let maxY = coords.map { $0.y }.max()!
    var gridItems = [[String]]()

    for y in 0...maxY {
      var row = [String]()
      for x in 0...maxX {
        if tmpCoords.contains(Point(x: x, y: y)) {
          row.append("#")
        }
        else {
          row.append(".")
        }
      }

      gridItems.append(row)
    }

    return Grid(items: gridItems)
  }

  func part1() -> String {
    let maxX = coords.map { $0.x }.max()!
    let maxY = coords.map { $0.y }.max()!
    let grid = gridAfterFallenBytes(numBytes: numBytesToFall)
    let graph = gridToDjikstraGraph(grid: grid)
    let distance = dijkstra(
      graph: graph,
      source: Point(x: 0, y: 0),
      target: Point(
        x: maxX,
        y: maxY
      ),
      canVisit: { _, to in
        grid.at(point: to) == "."
      }
    )!
    return String(distance)
  }

  func part2() -> String {
    let maxX = coords.map { $0.x }.max()!
    let maxY = coords.map { $0.y }.max()!

    var min = 0
    var max = coords.count
    var mid = max / 2
    while mid != max && mid != min {
      let grid = gridAfterFallenBytes(numBytes: mid)
      let graph = gridToDjikstraGraph(grid: grid)
      if dijkstra(
        graph: graph,
        source: Point(x: 0, y: 0),
        target: Point(
          x: maxX,
          y: maxY
        ),
        canVisit: { _, to in
          grid.at(point: to) == "."
        }
      ) == nil {
        // dropped too many, need to lower max
        // min stays the same
        max = mid
      } else {
        // dropped too few, need to raise min
        min = mid
        // max stays the same
      }

      mid = ((max - min) / 2) + min
    }

    let coord = coords[mid]
    return String("\(coord.x),\(coord.y)")
  }
}
