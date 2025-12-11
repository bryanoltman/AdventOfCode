import Foundation

public class Day11 {
  public static func parseInput(raw: String) -> [String: [String]] {
    var map = [String: [String]]()
    let lines = raw.split(separator: "\n")
    for line in lines {
      let parts = line.trimmingCharacters(in: .whitespacesAndNewlines).split(separator: ":")
      let value = String(parts.first!)
      let destinations = parts[1].split(separator: " ").map { String($0) }
      if map[value] == nil {
        map[value] = destinations
      }
      else {
        map[value]?.append(contentsOf: destinations)
      }
    }

    return map
  }


  static func numPaths(map: [String: [String]], start: String, end: String) -> Int {
    var currentCounts = [String: Int]()
    currentCounts[start] = 1
    var shouldContinue = true
    while shouldContinue {
      var nextCounts = [String: Int]()
      for k in map.keys {
        nextCounts[k] = 0
      }
      nextCounts[end] = currentCounts[end] ?? 0

      for (k, v) in currentCounts.filter({ $1 > 0 && $0 != end }) {
        guard let nextSteps = map[k] else {
          continue
        }
        for nextStep in nextSteps {
          guard let count = nextCounts[nextStep] else {
            continue
          }

          nextCounts[nextStep] = count + v
        }
      }

      currentCounts = nextCounts
      shouldContinue = false
      for (k, v) in nextCounts {
        if v != 0 && k != end {
          shouldContinue = true
          break
        }
      }
    }

    return currentCounts[end]!
  }

  public static func part1(map: [String: [String]]) -> Int {
    return numPaths(map: map, start: "you", end: "out")
  }

  public static func part2(map: [String: [String]]) -> Int {
    let svrToFftPaths = numPaths(map: map, start: "svr", end: "fft")
    let fftToDacPaths = numPaths(map: map, start: "fft", end: "dac")
    let dacToOutPaths = numPaths(map: map, start: "dac", end: "out")

    let svrToDacPaths = numPaths(map: map, start: "svr", end: "dac")
    let dacToFftPaths = numPaths(map: map, start: "dac", end: "fft")
    let fftToOutPaths = numPaths(map: map, start: "fft", end: "out")

    return svrToFftPaths * fftToDacPaths * dacToOutPaths + svrToDacPaths * dacToFftPaths
      * fftToOutPaths
  }
}
