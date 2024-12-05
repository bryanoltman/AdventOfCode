import Foundation

struct Point {
  let x: Int
  let y: Int

  static func + (lhs: Point, rhs: Point) -> Point {
    return Point(x: lhs.x + rhs.x, y: lhs.y + rhs.y)
  }

}

struct Day04: AdventDay {
  init(data: String) {
    self.data = data
    grid =
      data.split(separator: "\n")
      .map { row in
        row.map { String($0) }
      }
  }

  var data: String

  let grid: [[String]]

  // Returns 1 if xmas is found, 0 if not
  func findXmas(xPos: Point, direction: Point) -> Int {
    let mPos = xPos + direction
    let aPos = mPos + direction
    let sPos = aPos + direction

    if sPos.x < 0 || sPos.x >= grid[0].count || sPos.y < 0 || sPos.y >= grid.count {
      return 0
    }

    if grid[mPos.y][mPos.x] == "M" && grid[aPos.y][aPos.x] == "A" && grid[sPos.y][sPos.x] == "S" {
      return 1
    }
    else {
      return 0
    }
  }

  func findXmases(xPos: Point) -> Int {
    return
      // Up + Left
      findXmas(xPos: xPos, direction: Point(x: -1, y: -1))
      // Up
      + findXmas(xPos: xPos, direction: Point(x: 0, y: -1))
      // Up + Right
      + findXmas(xPos: xPos, direction: Point(x: 1, y: -1))
      // Right
      + findXmas(xPos: xPos, direction: Point(x: 1, y: 0))
      // Down Right
      + findXmas(xPos: xPos, direction: Point(x: 1, y: 1))
      // Down
      + findXmas(xPos: xPos, direction: Point(x: 0, y: 1))
      // Down + left
      + findXmas(xPos: xPos, direction: Point(x: -1, y: 1))
      // Left
      + findXmas(xPos: xPos, direction: Point(x: -1, y: 0))
  }

  func part1() -> Int {
    var numXmases = 0
    for y in 0..<grid.count {
      for x in 0..<grid[0].count {
        if grid[y][x] == "X" {
          numXmases += findXmases(xPos: Point(x: x, y: y))
        }
      }
    }

    return numXmases
  }

  func part2() -> Int {
    return 0
  }
}
