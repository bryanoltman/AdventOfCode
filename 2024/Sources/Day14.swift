struct Robot {
  let position: Point
  let velocity: Point
}

struct Day14: AdventDay {
  init(data: String) {
    self.init(data: data, width: 101, height: 103)
  }

  init(data: String, width: Int, height: Int) {
    self.width = width
    self.height = height
    self.data = data
    self.robots = data.split(separator: "\n").map {
      Day14.parseRobotLine(String($0))
    }
  }

  static func parseRobotLine(_ line: String) -> Robot {
    let parts = line.trimmingCharacters(in: .whitespacesAndNewlines).split(
      separator: " ")
    let positionStr = parts[0].replacingOccurrences(of: "p=", with: "")
    let velocityStr = parts[1].replacingOccurrences(of: "v=", with: "")

    let positionParts = positionStr.split(separator: ",")
    let velocityParts = velocityStr.split(separator: ",")

    return Robot(
      position: Point(x: Int(positionParts[0])!, y: Int(positionParts[1])!),
      velocity: Point(x: Int(velocityParts[0])!, y: Int(velocityParts[1])!)
    )
  }

  var data: String

  let robots: [Robot]

  let width: Int
  let height: Int

  func robotPositions(seconds: Int) -> [Robot] {
    var updatedRobots = [Robot]()
    for r in robots {
      var x = r.position.x
      var y = r.position.y

      x += width * seconds
      y += height * seconds

      x += r.velocity.x * seconds
      y += r.velocity.y * seconds

      x = x % width
      y = y % height

      updatedRobots
        .append(Robot(position: Point(x: x, y: y), velocity: r.velocity))
    }

    return updatedRobots
  }

  func quadrantCounts(positions: [Point]) -> [Int: Int] {
    var quadrants = [
      1: 0,
      2: 0,
      3: 0,
      4: 0,
    ]

    let quad1XRange = 0..<width / 2
    let quad2XRange = (width / 2 + 1)..<width
    let quad3XRange = (width / 2 + 1)..<width
    let quad4XRange = 0..<width / 2

    let quad1YRange = 0..<height / 2
    let quad2YRange = 0..<height / 2
    let quad3YRange = (height / 2 + 1)..<height
    let quad4YRange = (height / 2 + 1)..<height

    for p in positions {
      if quad1XRange.contains(p.x) && quad1YRange.contains(p.y) {
        quadrants[1, default: 0] += 1
      } else if quad2XRange.contains(p.x) && quad2YRange.contains(p.y) {
        quadrants[2, default: 0] += 1
      } else if quad3XRange.contains(p.x) && quad3YRange.contains(p.y) {
        quadrants[3, default: 0] += 1
      } else if quad4XRange.contains(p.x) && quad4YRange.contains(p.y) {
        quadrants[4, default: 0] += 1
      }
    }

    return quadrants
  }

  func part1() -> Int {
    let updatedRobots = robotPositions(seconds: 100)
    let positions = updatedRobots.map { $0.position }
    let quadrants = quadrantCounts(positions: positions)
    return quadrants[1]! * quadrants[2]! * quadrants[3]! * quadrants[4]!
  }

  func part2() -> Int {
    return 0
  }
}
