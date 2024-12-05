struct SortOrder {
  let first: Int
  let last: Int
}

struct OrderRule {
  var before: Set<Int>
  var after: Set<Int>
}

struct Day05: AdventDay {
  init(data: String) {
    self.data = data
    let parts = data.split(separator: "\n\n")

    sortOrders = parts[0].split(separator: "\n")
      .map({ line in
        let nums = line.split(separator: "|")
        return SortOrder(first: Int(nums[0])!, last: Int(nums[1])!)
      })

    orderRules = [:]

    for s in sortOrders {
      var orderRule = orderRules[s.first, default: OrderRule(before: [], after: [])]
      orderRule.after.insert(s.last)
      orderRules[s.first] = orderRule

      orderRule = orderRules[s.last, default: OrderRule(before: [], after: [])]
      orderRule.before.insert(s.first)
      orderRules[s.last] = orderRule
    }

    updates = parts[1].split(separator: "\n")
      .map({ line in
        line.split(separator: ",").map { Int($0)! }
      })
  }

  let data: String

  let sortOrders: [SortOrder]
  var orderRules: [Int: OrderRule]

  let updates: [[Int]]

  func isUpdateCorrectlyOrdered(update: [Int]) -> Bool {
    for (i, num) in update.enumerated() {
      guard let orderRule = orderRules[num] else {
        continue
      }

      for ii in i..<update.count {
        if orderRule.before.contains(update[ii]) {
          return false
        }
      }
    }

    return true
  }

  func part1() -> Int {
    return
      updates.filter { isUpdateCorrectlyOrdered(update: $0) }
      .map { $0[$0.count / 2] }
      .reduce(0, +)
  }

  func fixOrdering(update: [Int]) -> [Int] {
    var ret = update

    while !isUpdateCorrectlyOrdered(update: ret) {
      for (i, num) in ret.enumerated() {
        guard let orderRule = orderRules[num] else {
          continue
        }

        for ii in i..<ret.count {
          if orderRule.before.contains(ret[ii]) {
            ret.swapAt(i, ii)
          }
        }
      }
    }

    return ret
  }

  func part2() -> Int {
    return
      updates.filter { !isUpdateCorrectlyOrdered(update: $0) }
      .map { fixOrdering(update: $0) }
      .map { $0[$0.count / 2] }
      .reduce(0, +)
  }
}
