extension Array {
  var tail: Array {
    Array(dropFirst())
  }
}

extension Array where Element: Equatable {
  func firstIndexOf(subsequence: [Element]) -> Int? {
    let subseqCount = subsequence.count
    for i in 0..<(self.count - subseqCount) {
      if Array(self[i..<i + subseqCount]) == subsequence {
        return i
      }
    }

    return nil
  }
}
