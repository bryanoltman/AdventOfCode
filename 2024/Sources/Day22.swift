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
    num % 16777216
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
    codes.map { c in
      var n = c
      for _ in 0..<2000 {
        n = evolve(n)
      }
      
      return n
    }
    .reduce(0, +)
  }

  func part2() -> Int {
    return 0
  }
}
