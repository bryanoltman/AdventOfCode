struct Day01: AdventDay{
  var data: String
  
  // Splits input data into its component parts and convert from string.
  var entities: [[Int]] {
    data.split(separator: "\n").map {
      $0.split(separator: "   ").compactMap { Int($0) }
    }
  }
  
  func part1() -> Int {
    let sortedLeftNums = entities.map{ row in row.first!}.sorted()
    let sortedRightNums = entities.map{row in row.last!} .sorted()
    return zip(sortedLeftNums, sortedRightNums)
      .map { r in abs(r.0 - r.1)}
      .reduce(0, +)
  }
  
  func part2() -> Int {
    let leftNums = entities.map{ row in row.first!}
    let rightNums = entities.map{row in row.last!}
    var counts: [Int: Int] = [:]
    for num in rightNums {
      counts[num] = (counts[num] ?? 0) + 1
    }
    
    return leftNums.map { i in
      i * (counts[i] ?? 0)
    }
    .reduce(0, +)
  }
}
