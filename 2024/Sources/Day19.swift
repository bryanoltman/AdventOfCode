struct Day19: AdventDay {
  init(data: String) {
    self.data = data
    let parts = data.split(separator: "\n\n")
    self.patterns = parts[0].split(separator: ",")
      .map { $0.trimmingCharacters(in: .whitespacesAndNewlines) }
    self.candidateDesigns = parts[1].split(separator: "\n").map { String($0) }
  }

  var data: String

  let patterns: [String]

  let candidateDesigns: [String]

  func numWaysToMakeDesign(_ design: String, designCache: inout [String: Int]) -> Int {
    if design.isEmpty {
      return 1
    }

    if let configs = designCache[design] {
      return configs
    }

    var configs = 0
    for pattern in patterns {
      guard design.starts(with: pattern) else {
        continue
      }

      let nextDesign = String(design.dropFirst(pattern.count))
      let numConfigs = numWaysToMakeDesign(nextDesign, designCache: &designCache)
      configs += numConfigs
    }

    designCache[design] = configs
    return configs
  }

  func part1() -> Int {
    var designCache = [String: Int]()
    return candidateDesigns.count { design in
      if !patterns.contains(where: { design.hasSuffix($0) }) {
        return false
      }
      return numWaysToMakeDesign(design, designCache: &designCache) > 0
    }
  }

  func part2() -> Int {
    var designCache2 = [String: Int]()
    return
      candidateDesigns.map { design in
        if !patterns.contains(where: { design.hasSuffix($0) }) {
          return 0
        }
        return numWaysToMakeDesign(design, designCache: &designCache2)
      }
      .reduce(0, +)
  }
}
