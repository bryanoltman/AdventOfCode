struct Day22: AdventDay {
  init(data: String) {
    self.data = data
    codes = data.trimmingCharacters(in: .whitespacesAndNewlines)
      .split(separator: "\n")
      .map { Int($0)! }
  }

  var data: String

  let codes: [Int]

  func mix(_ num: Int, with other: Int) -> Int {
    num ^ other
  }

  func prune(_ num: Int) -> Int {
    num % 16_777_216
  }

  func evolve(_ num: Int) -> Int {
    // Calculate the result of multiplying the secret number by 64.
    // Then, mix this result into the secret number.
    // Finally, prune the secret number.
    var ret = prune(mix(num * 64, with: num))

    // Calculate the result of dividing the secret number by 32.
    // Round the result down to the nearest integer.
    // Then, mix this result into the secret number.
    // Finally, prune the secret number.
    ret = prune(mix(ret / 32, with: ret))

    // Calculate the result of multiplying the secret number by 2048.
    // Then, mix this result into the secret number.
    // Finally, prune the secret number.
    ret = prune(mix(ret * 2048, with: ret))

    return ret
  }

  func part1() -> Int {
    // Evolve each code 2000 times and sum
    codes.map { c in
      var n = c
      for _ in 0..<2000 {
        n = evolve(n)
      }

      return n
    }
    .reduce(0, +)
  }

  func lastNumbers() -> [[Int]] {
    codes.map { c in
      var n = c
      var nums = [Int]()
      for _ in 0..<2000 {
        n = evolve(n)
        nums.append(n % 10)
      }

      return nums
    }
  }

  func changes(lastNumbers: [[Int]]) -> [[Int]] {
    lastNumbers.map { nums in
      var ret = [0]
      for i in 1..<nums.count {
        let diff = nums[i] - nums[i - 1]
        print("diff is \(diff)")
        ret.append(diff)
      }

      return ret
    }
  }

  let seqLength = 4

  // Maps sequences to the number of change lists they occur in. Sequences will
  // be counted at most once per change list.
  func seqsToFreqs(changes: [[Int]]) -> [[Int]: Int] {
    var ret = [[Int]: Int]()
    for c in changes {
      var changeSeqs: Set<[Int]> = Set()
      for i in 1..<(c.count - seqLength) {
        let seq = Array(c[i..<i + seqLength])
        changeSeqs.insert(seq)
      }

      for seq in changeSeqs {
        ret[seq, default: 0] += 1
      }
    }

    return ret
  }

  func findBestSeq() -> [Int] {
    let lastNumbers = lastNumbers()
    let changes = changes(lastNumbers: lastNumbers)

    let seqsToFreqs = seqsToFreqs(changes: changes)
    var freqsToSeqs = [Int: [[Int]]]()
    for (k, v) in seqsToFreqs {
      freqsToSeqs[v, default: []].append(k)
    }
    let sortedKeys = Array(freqsToSeqs.keys.sorted().reversed())

    var maxPrice = Int.min
    var bestSeq = [Int]()
    var i = 0
    for key in sortedKeys[0..<20] {
      print("key is \(key). processing \(freqsToSeqs[key]!.count) seqs")
      for seq in freqsToSeqs[key]! {
        let price = computePrice(
          changeSeq: seq, lastNumbers: lastNumbers, changes: changes)
        if price > maxPrice {
          print("NEW BEST PRICE: \(price)")
          maxPrice = price
          bestSeq = seq
        }

        i += 1
      }
    }

    return bestSeq
  }

  func computePrice(
    changeSeq: [Int], lastNumbers: [[Int]], changes: [[Int]]
  ) -> Int {
    var sum = 0
    for (last, change) in zip(lastNumbers, changes) {
      guard let idx = change.firstIndexOf(subsequence: changeSeq) else {
        continue
      }
      let targetIdx = idx + seqLength - 1
      //      print("targetIdx is \(targetIdx)")
      let price = last[targetIdx]
      sum += price
    }

    return sum
  }

  func part2() -> Int {
    // Answer is 1619
    //    let seq = findBestSeq()
    let lastNumbers = lastNumbers()
    return computePrice(
//      changeSeq: [0, 2, 0, 0],
            changeSeq: [-2,1,-1,3],
      lastNumbers: lastNumbers,
      changes: changes(lastNumbers: lastNumbers)
    )
  }
}
