//
//  ContentView.swift
//  AOC UI
//
//  Created by Bryan Oltman on 12/1/24.
//

import SwiftUI

struct ContentView: View {
  var body: some View {
    Day01View(
      viewModel: Part1ViewModel(
        leftNumbers: Day01.leftNums,
        rightNumbers: Day01.rightNums,
        step: .start
      )
    )
  }
}

#Preview {
  ContentView()
}
