//
//  main.cpp
//  01
//
//  Created by Bryan Oltman on 12/1/23.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream> //std::stringstream

#include "day01.hpp"

int main(int argc, const char * argv[]) {
  auto input = ReadInput("/Users/bryanoltman/Documents/AdventOfCode/2023/inputs/01.txt");
  std::cout << "Part 1: " << PartOne(input) << "\n";
  return 0;
}
