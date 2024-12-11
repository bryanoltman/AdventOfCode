struct Point: Equatable, Hashable {
  let x: Int
  let y: Int

  static func + (lhs: Point, rhs: Point) -> Point {
    Point(x: lhs.x + rhs.x, y: lhs.y + rhs.y)
  }

  static func - (lhs: Point, rhs: Point) -> Point {
    Point(x: lhs.x - rhs.x, y: lhs.y - rhs.y)
  }

  static func * (lhs: Point, rhs: Int) -> Point {
    Point(x: lhs.x * rhs, y: lhs.y * rhs)
  }

  static let up = Point(x: 0, y: -1)

  static let down = Point(x: 0, y: 1)

  static let right = Point(x: 1, y: 0)

  static let left = Point(x: -1, y: 0)

  func manhattanDistance(from other: Point) -> Int {
    abs(self.y - other.y) + abs(self.x - other.x)
  }
}

struct Grid<T: Equatable> {
  init(string: String, itemConverter: (String) -> T) {
    items = string.split(separator: "\n")
      .map { line in
        line.map { itemConverter(String($0)) }
      }
    self.points = Grid<T>.pointsFromItems(items: items)
  }

  init(items: [[T]]) {
    self.items = items
    self.points = Grid<T>.pointsFromItems(items: items)
  }

  let items: [[T]]

  let points: Set<Point>

  static private func pointsFromItems(items: [[T]]) -> Set<Point> {
    var allPoints = Set<Point>()
    for x in 0..<items.count {
      for y in 0..<items[0].count {
        allPoints.insert(Point(x: x, y: y))
      }
    }

    return allPoints
  }

  func at(point: Point) -> T {
    items[point.y][point.x]
  }

  func contains(point: Point) -> Bool {
    return !(point.x < 0 || point.x >= items[0].count || point.y < 0 || point.y >= items.count)
  }

  func findFirst(item: T) -> Point? {
    return points.first { at(point: $0) == item }
  }

  func neighbors(point: Point) -> Set<Point> {
    let candidates = [
      point + Point(x: 0, y: 1),
      point + Point(x: 0, y: -1),
      point + Point(x: 1, y: 0),
      point + Point(x: -1, y: 0),
    ]
    return Set(candidates.filter(contains(point:)))
  }
}
