extension Array {
  var tail: Array {
    Array(dropFirst())
  }
}
