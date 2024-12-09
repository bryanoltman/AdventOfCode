struct Point: Equatable, Hashable {
  let x: Int
  let y: Int

  static func + (lhs: Point, rhs: Point) -> Point {
    return Point(x: lhs.x + rhs.x, y: lhs.y + rhs.y)
  }

  static let up = Point(x: 0, y: -1)

  static let down = Point(x: 0, y: 1)

  static let right = Point(x: 1, y: 0)

  static let left = Point(x: -1, y: 0)
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

  let items: [[T]]

  func at(point: Point) -> T {
    items[point.y][point.x]
  }

  func contains(point: Point) -> Bool {
    return !(point.x < 0 || point.x >= items[0].count || point.y < 0 || point.y >= items.count)
  }

  func findFirst(item: T) -> Point? {
    for x in 0..<items.count {
      for y in 0..<items[0].count {
        if items[y][x] == item {
          return Point(x: x, y: y)
        }
      }
    }

    return nil
  }

}
