import Foundation

struct Day01 {
  enum Direction {
    case right, left
  }

  struct Rotation {
    let direction: Direction
    let ticks: Int
  }

  static func parseInput(raw: String) -> [Rotation] {
    return raw.split(whereSeparator: \.isNewline).map { line in
      let dirChar = line.first
      var lineCopy = line
      lineCopy.removeFirst()
      return Rotation(direction: dirChar == "R" ? .right : .left, ticks: Int(lineCopy)!)
    }
  }

  static func part1(rotations: [Rotation]) -> Int {
    var dialValue = 50
    var zeroCount = 0
    for r in rotations {
      switch r.direction {
      case .right:
        dialValue += r.ticks
      case .left:
        dialValue -= r.ticks
      }

      while dialValue < 0 {
        dialValue += 100
      }

      while dialValue >= 100 {
        dialValue -= 100
      }

      if dialValue == 0 {
        zeroCount += 1
      }
    }

    return zeroCount
  }

  static func part2(rotations: [Rotation]) -> Int {
    var dialValue = 50
    var zeroCount = 0
    for r in rotations {
      var nextDialValue =
        switch r.direction {
        case .right: dialValue + r.ticks
        case .left: dialValue - r.ticks
        }

      if nextDialValue >= 100 {
        while nextDialValue >= 100 {
          nextDialValue -= 100
          zeroCount += 1
        }
        if nextDialValue == 0 {
          zeroCount -= 1
        }
      }

      if nextDialValue < 0 {
        if dialValue == 0 {
          zeroCount -= 1
        }
        while nextDialValue < 0 {
          nextDialValue += 100
          zeroCount += 1
        }
      }

      if nextDialValue == 0 {
        zeroCount += 1
      }

      dialValue = nextDialValue
    }

    return zeroCount
  }
}
