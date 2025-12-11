import Foundation

public class Day04 {
  public static func parseInput(_ input: String) -> [[String]] {
    return input.split(separator: "\n")
      .map {
        $0.split(separator: "").map { String($0) }
      }
  }

  struct Point {
    let x: Int
    let y: Int
  }

  static func neighborPoints<T>(map: [[T]], point p: Point) -> [Point] {
    let candidates = [
      Point(x: p.x - 1, y: p.y - 1),
      Point(x: p.x - 1, y: p.y),
      Point(x: p.x - 1, y: p.y + 1),

      Point(x: p.x, y: p.y - 1),
      Point(x: p.x, y: p.y + 1),

      Point(x: p.x + 1, y: p.y - 1),
      Point(x: p.x + 1, y: p.y),
      Point(x: p.x + 1, y: p.y + 1),
    ]

    return candidates.filter { $0.x >= 0 && $0.y >= 0 && $0.x < map[0].count && $0.y < map.count }
  }

  public static func part1(_ input: [[String]]) -> Int {
    var sum = 0
    for y in 0..<input.count {
      for x in 0..<input[y].count {
        guard input[y][x] == "@" else {
          continue
        }
        let point = Point(x: x, y: y)
        let neighbors = neighborPoints(map: input, point: point).map { input[$0.y][$0.x] }
        if neighbors.count(where: { $0 == "@" }) < 4 {
          sum += 1
        }
      }
    }

    return sum
  }

  public static func part2(_ input: [[String]]) -> Int {
    var sum = 0
    var hasChanged = false
    var currentMap = input
    repeat {
      hasChanged = false
      var nextMap: [[String]] = []
      for y in 0..<currentMap.count {
        var nextRow = [String]()
        for x in 0..<currentMap[y].count {
          guard currentMap[y][x] == "@" else {
            nextRow.append(".")
            continue
          }
          let point = Point(x: x, y: y)
          let neighbors = neighborPoints(map: currentMap, point: point).map { currentMap[$0.y][$0.x] }
          if neighbors.count(where: { $0 == "@" }) < 4 {
            nextRow.append(".")
            sum += 1
            hasChanged = true
          } else {
            nextRow.append("@")
          }
        }
        nextMap.append(nextRow)
      }

      currentMap = nextMap
    } while hasChanged
    return sum
  }
}
