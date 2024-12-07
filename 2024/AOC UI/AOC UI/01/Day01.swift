import SwiftUI

struct Day01View: View {
  @StateObject var viewModel: Part1ViewModel

  func moveForward() {
    let next = nextViewModel
    withAnimation {
      viewModel.leftNumbers = next.leftNumbers
      viewModel.rightNumbers = next.rightNumbers
      viewModel.sum = next.sum
      viewModel.step = next.step
    }
  }

  var nextViewModel: Part1ViewModel {
    switch viewModel.step {
    case .start:
      return Part1ViewModel(
        leftNumbers: Day01.leftNums.sorted(),
        rightNumbers: Day01.rightNums,
        step: .sortLeft
      )
    case .sortLeft:
      return Part1ViewModel(
        leftNumbers: Day01.leftNums.sorted(),
        rightNumbers: Day01.rightNums.sorted(),
        step: .sortRight
      )
    case .sortRight:
      return Part1ViewModel(
        leftNumbers: Day01.leftNums.sorted(),
        rightNumbers: Day01.rightNums.sorted(),
        step: .addRow(0, 0)
      )
    case .addRow(let row, let sum):
      let nextRow = row + 1
      if nextRow < Day01.leftNums.count {
        let nextSum = sum + abs(Day01.leftNums.sorted()[row] - Day01.rightNums.sorted()[row])
        return Part1ViewModel(
          leftNumbers: Day01.leftNums.sorted(),
          rightNumbers: Day01.rightNums.sorted(),
          step: .addRow(nextRow, nextSum)
        )
      }
      else {
        let nextSum = sum + abs(Day01.leftNums.sorted().last! - Day01.rightNums.sorted().last!)
        return Part1ViewModel(
          leftNumbers: Day01.leftNums.sorted(),
          rightNumbers: Day01.rightNums.sorted(),
          step: .done(nextSum)
        )
      }
    case .done(_):
      return viewModel
    }
  }

  var highlightRow: Int? {
    if case .addRow(let row, _) = viewModel.step {
      return row
    }

    return nil
  }

  var body: some View {
    VStack {
      HStack(alignment: .top) {
        VStack {
          ForEach(Array(viewModel.leftNumbers.enumerated()), id: \.element) { i, num in
            Text("\(num)")
              .scaleEffect(x: highlightRow == i ? 1.5 : 1, y: highlightRow == i ? 1.5 : 1)
              .animation(.spring(), value: highlightRow == i)
          }
        }

        VStack {
          ForEach(Array(viewModel.rightNumbers.enumerated()), id: \.element) { i, num in
            Text("\(num)")
              .scaleEffect(x: highlightRow == i ? 1.5 : 1, y: highlightRow == i ? 1.5 : 1)
              .animation(.spring(), value: highlightRow == i)

          }
        }

        if case .addRow(let row, let sum) = viewModel.step {
          Text("\(sum)")
            .scaleEffect(x: 1, y: 1)
            .offset(x: 0, y: CGFloat(row * 16))
            .animation(.spring(), value: false)
        }
        if case .done(let sum) = viewModel.step {
          Text("\(sum)")
            .scaleEffect(x: 1.5, y: 1.5)
            .offset(x: 0, y: CGFloat(Day01.leftNums.count * 16))
            .animation(.spring(), value: true)
        }
      }
      .padding()

      Button("Next") {
        moveForward()
      }
    }
  }
}

#Preview {
  Day01View(
    viewModel: Part1ViewModel(
      leftNumbers: Day01.leftNums,
      rightNumbers: Day01.rightNums,
      step: .start
    )
  )
}

class Part1ViewModel: ObservableObject {
  init(leftNumbers: [Int], rightNumbers: [Int], step: Day01Part1Step) {
    self.leftNumbers = leftNumbers
    self.rightNumbers = rightNumbers
    self.step = step
  }

  @Published var leftNumbers: [Int]

  @Published var rightNumbers: [Int]

  @Published var sum: Int?

  @Published var step: Day01Part1Step
}

enum Day01Part1Step {
  case start
  case sortLeft
  case sortRight
  case addRow(Int, Int)
  case done(Int)
}

struct Day01 {

  var data: String

  static var entities: [[Int]] {
    [
      [3, 4],
      [4, 3],
      [2, 5],
      [1, 3],
      [3, 9],
      [3, 3],
    ]
  }

  static var leftNums: [Int] { entities.map { row in row.first! } }

  static var rightNums: [Int] { entities.map { row in row.last! } }

  func part1() -> Int {
    return zip(Day01.leftNums.sorted(), Day01.rightNums.sorted())
      .map { r in abs(r.0 - r.1) }
      .reduce(0, +)
  }

  func part2() -> Int {
    var counts: [Int: Int] = [:]
    for num in Day01.rightNums {
      counts[num] = (counts[num] ?? 0) + 1
    }

    return Day01.leftNums
      .map { i in
        i * (counts[i] ?? 0)
      }
      .reduce(0, +)
  }
}
