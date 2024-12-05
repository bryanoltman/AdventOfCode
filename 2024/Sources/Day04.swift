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

  func findMasX(topLeftPos: Point) -> Int {
    let aPos = topLeftPos + Point(x: 1, y: 1)
    let lowerLeftPos = topLeftPos + Point(x: 0, y: 2)
    let upperRightPos = topLeftPos + Point(x: 2, y: 0)
    let lowerRightPos = topLeftPos + Point(x: 2, y: 2)

    if lowerRightPos.x < 0 || lowerRightPos.x >= grid[0].count || lowerRightPos.y < 0
      || lowerRightPos.y >= grid.count
    {
      return 0
    }

    let a = grid[aPos.y][aPos.x]
    if a != "A" {
      return 0
    }

    let topLeft = grid[topLeftPos.y][topLeftPos.x]
    let bottomLeft = grid[lowerLeftPos.y][lowerLeftPos.x]
    let topRight = grid[upperRightPos.y][upperRightPos.x]
    let bottomRight = grid[lowerRightPos.y][lowerRightPos.x]

    // S on top, M on bottom
    if topLeft == "S" && topRight == "S" && bottomLeft == "M" && bottomRight == "M" {
      return 1
    }
    // M on top, S on bottom
    else if topLeft == "M" && topRight == "M" && bottomLeft == "S" && bottomRight == "S" {
      return 1
    }
    // M on left, S on right
    else if topLeft == "M" && topRight == "S" && bottomLeft == "M" && bottomRight == "S" {
      return 1
    }
    // S on left, M or night
    else if topLeft == "S" && topRight == "M" && bottomLeft == "S" && bottomRight == "M" {
      return 1
    }

    return 0
  }

  func part2() -> Int {
    var numMasXes = 0
    for y in 0..<grid.count {
      for x in 0..<grid[0].count {
        numMasXes += findMasX(topLeftPos: Point(x: x, y: y))
      }
    }

    return numMasXes
  }
}
