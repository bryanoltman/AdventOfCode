import SwiftUI

struct Day06View: View {
  @StateObject var viewModel: Day06Part1ViewModel

  func moveForward() {
    //    let next = nextViewModel
    //    withAnimation {
    //      viewModel.leftNumbers = next.leftNumbers
    //      viewModel.rightNumbers = next.rightNumbers
    //      viewModel.sum = next.sum
    //    }
  }

  //  var nextViewModel: Day06Part1ViewModel {
  //    switch viewModel.step {
  //    case .start:
  //      return Part1ViewModel(
  //        leftNumbers: Day01.leftNums.sorted(),
  //        rightNumbers: Day01.rightNums,
  //        step: .sortLeft
  //      )
  //    case .sortLeft:
  //      return Part1ViewModel(
  //        leftNumbers: Day01.leftNums.sorted(),
  //        rightNumbers: Day01.rightNums.sorted(),
  //        step: .sortRight
  //      )
  //    case .sortRight:
  //      return Part1ViewModel(
  //        leftNumbers: Day01.leftNums.sorted(),
  //        rightNumbers: Day01.rightNums.sorted(),
  //        step: .addRow(0, 0)
  //      )
  //    case .addRow(let row, let sum):
  //      let nextRow = row + 1
  //      if nextRow < Day01.leftNums.count {
  //        let nextSum = sum + abs(Day01.leftNums.sorted()[row] - Day01.rightNums.sorted()[row])
  //        return Part1ViewModel(
  //          leftNumbers: Day01.leftNums.sorted(),
  //          rightNumbers: Day01.rightNums.sorted(),
  //          step: .addRow(nextRow, nextSum)
  //        )
  //      }
  //      else {
  //        let nextSum = sum + abs(Day01.leftNums.sorted().last! - Day01.rightNums.sorted().last!)
  //        return Part1ViewModel(
  //          leftNumbers: Day01.leftNums.sorted(),
  //          rightNumbers: Day01.rightNums.sorted(),
  //          step: .done(nextSum)
  //        )
  //      }
  //    case .done(_):
  //      return viewModel
  //    }
  //  }

  //  var highlightRow: Int? {
  //    if case .addRow(let row, _) = viewModel.step {
  //      return row
  //    }
  //
  //    return nil
  //  }

  var body: some View {
    VStack {
      ForEach(viewModel.grid.items, id: \.self) { line in
        HStack {
          ForEach(line, id: \.self) { char in
            Text(char)
          }
        }
      }

      //      HStack(alignment: .top) {
      //        VStack {
      //          ForEach(Array(viewModel.leftNumbers.enumerated()), id: \.element) { i, num in
      //            Text("\(num)")
      //              .scaleEffect(x: highlightRow == i ? 1.5 : 1, y: highlightRow == i ? 1.5 : 1)
      //              .animation(.spring(), value: highlightRow == i)
      //          }
      //        }
      //
      //        VStack {
      //          ForEach(Array(viewModel.rightNumbers.enumerated()), id: \.element) { i, num in
      //            Text("\(num)")
      //              .scaleEffect(x: highlightRow == i ? 1.5 : 1, y: highlightRow == i ? 1.5 : 1)
      //              .animation(.spring(), value: highlightRow == i)
      //
      //          }
      //        }
      //
      //        if case .addRow(let row, let sum) = viewModel.step {
      //          Text("\(sum)")
      //            .scaleEffect(x: 1, y: 1)
      //            .offset(x: 0, y: CGFloat(row * 16))
      //            .animation(.spring(), value: false)
      //        }
      //        if case .done(let sum) = viewModel.step {
      //          Text("\(sum)")
      //            .scaleEffect(x: 1.5, y: 1.5)
      //            .offset(x: 0, y: CGFloat(Day01.leftNums.count * 16))
      //            .animation(.spring(), value: true)
      //        }
      //      }
      //      .padding()
      //
      Button("Next") {
        moveForward()
      }
      .padding(EdgeInsets(top: 10, leading: 10, bottom: 10, trailing: 10))
    }
    .padding()
  }
}

#Preview {
  Day06View(
    viewModel: Day06Part1ViewModel(
      direction: Point.up, position: Point(x: 0, y: 0), grid: Day06.grid, visitedPositions: Set()
    )
  )
}

class Day06Part1ViewModel: ObservableObject {
  init(direction: Point, position: Point, grid: Grid<String>, visitedPositions: Set<Point>) {
    self.direction = direction
    self.position = position
    self.grid = grid
    self.visitedPositions = visitedPositions
  }

  @Published var direction: Point

  @Published var position: Point

  @Published var grid: Grid<String>

  @Published var visitedPositions: Set<Point>
}

//enum Day06Part1Step {
//  case start
//  case sortLeft
//  case sortRight
//  case addRow(Int, Int)
//  case done(Int)
//}

struct Day06 {
  static let data = """
    ....#.....
    .........#
    ..........
    ..#.......
    .......#..
    ..........
    .#..^.....
    ........#.
    #.........
    ......#...
    """

  static let grid = Grid(
    string: data,
    itemConverter: { s in
      s
    }
  )

  func part1() -> Int {
    return zip(Day01.leftNums.sorted(), Day01.rightNums.sorted())
      .map { r in abs(r.0 - r.1) }
      .reduce(0, +)
  }


  func part2() -> Int {
    return 0
  }
}
