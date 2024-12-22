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

  func canMakeDesignBacktrack(_ design: String, designCache: inout [String: Bool]) -> Bool {
    if design.isEmpty {
      return true
    }

    if let result = designCache[design] {
      return result
    }

    for pattern in patterns {
      guard design.starts(with: pattern) else {
        continue
      }

      let nextDesign = String(design.dropFirst(pattern.count))
      if canMakeDesignBacktrack(nextDesign, designCache: &designCache) {
        designCache[nextDesign] = true
        return true
      }
    }

    designCache[design] = false
    return false
  }

  func part1() -> Int {
    var designCache = [String: Bool]()
    return candidateDesigns.count { design in
      if !patterns.contains(where: { design.hasSuffix($0) }) {
        return false
      }
      return canMakeDesignBacktrack(design, designCache: &designCache)
    }
  }

  func part2() -> Int {
    return 0
  }
}
