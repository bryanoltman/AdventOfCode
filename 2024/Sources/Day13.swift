struct ButtonPair {
  let buttonA: Point
  let buttonB: Point
  let prize: Point
}

struct Day13: AdventDay {
  init(data: String) {
    self.data = data
    self.buttonPairs =
      Day13
      .parseInput(data.trimmingCharacters(in: .whitespacesAndNewlines))
  }

  static func parseInput(_ input: String) -> [ButtonPair] {
    return input.split(separator: "\n\n")
      .map { parseButtonPair(String($0)) }
  }

  static func pointFromMatch(
    _ match: Regex<(Substring, Substring, Substring)>.Match
  ) -> Point {
    Point(x: Int(match.1)!, y: Int(match.2)!)
  }

  static func parseButtonPair(_ input: String) -> ButtonPair {
    let lines = input.split(separator: "\n")
    let buttonRegex = /(?:Button [AB]|Prize): X[\+=](\d+), Y[\+=](\d+)/
    let buttonA = try! buttonRegex.firstMatch(in: lines[0])
    let buttonB = try! buttonRegex.firstMatch(in: lines[1])
    let prize = try! buttonRegex.firstMatch(in: lines[2])

    return ButtonPair(
      buttonA: pointFromMatch(buttonA!),
      buttonB: pointFromMatch(buttonB!),
      prize: pointFromMatch(prize!)
    )
  }

  var data: String

  let buttonPairs: [ButtonPair]

  func getMin(buttonPair bp: ButtonPair) -> Int {
    let Rx = bp.prize.x
    let Ry = bp.prize.y
    let Ax = bp.buttonA.x
    let Ay = bp.buttonA.y
    let Bx = bp.buttonB.x
    let By = bp.buttonB.y
    let top = Bx * Ry - By * Rx
    let bot = Ay * Bx - Ax * By
    if top % bot != 0 {
      return 0
    }
    let Pa = top / bot
    if (Rx - (Pa * Ax)) % Bx != 0 {
      return 0
    }
    let Pb = (Rx - (Pa * Ax)) / Bx
    // A presses cost 3 tokens, B presses cost 1 token
    return Pa * 3 + Pb
  }

  func part1() -> Int {
    buttonPairs.map(getMin(buttonPair:)).reduce(0, +)
  }

  func part2() -> Int {
    buttonPairs
      .map {
        ButtonPair(
          buttonA: $0.buttonA,
          buttonB: $0.buttonB,
          prize: $0.prize + Point(x: 10_000_000_000_000, y: 10_000_000_000_000)
        )
      }
      .map(getMin(buttonPair:)).reduce(0, +)
  }
}
