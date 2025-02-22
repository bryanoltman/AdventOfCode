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

  // Assumes self and other share an axis
  func direction(to other: Point) -> Point {
    if other.x == x {
      return y < other.y ? Point.down : Point.up
    } else {
      return x < other.x ? Point.right : Point.left
    }
  }
}

struct Grid<T: Equatable> {
  init(string: String, itemConverter: (String) -> T) {
    items = string.split(separator: "\n")
      .map { line in
        line.map { itemConverter(String($0)) }
      }
  }

  init(items: [[T]]) {
    self.items = items
  }

  var items: [[T]]

  var points: Set<Point> {
    Grid<T>.pointsFromItems(items: items)
  }

  static private func pointsFromItems(items: [[T]]) -> Set<Point> {
    var allPoints = Set<Point>()
    for y in 0..<items.count {
      for x in 0..<items[0].count {
        allPoints.insert(Point(x: x, y: y))
      }
    }

    return allPoints
  }

  func at(point: Point) -> T {
    items[point.y][point.x]
  }

  func contains(point: Point) -> Bool {
    !(point.x < 0 || point.x >= items[0].count || point.y < 0
      || point.y >= items.count)
  }

  func filter(isIncluded: (T) -> Bool) -> [Point] {
    points.filter { p in isIncluded(at(point: p)) }
  }

  func findFirst(item: T) -> Point? {
    points.first { at(point: $0) == item }
  }

  mutating func swap(_ point: Point, _ otherPoint: Point) {
    let tmp = items[point.y][point.x]
    items[point.y][point.x] = items[otherPoint.y][otherPoint.x]
    items[otherPoint.y][otherPoint.x] = tmp
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

  func print() {
    for y in 0..<items.count {
      for x in 0..<items[y].count {
        Swift.print(items[y][x], terminator: "")
      }
      Swift.print()
    }
  }
}
