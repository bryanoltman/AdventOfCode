#include <iostream>

#include "12/12.h"

using namespace std;

int main(int argc, char const *argv[]) {
  Input input = ParseInput("inputs/12.txt");

  cout << "Part One: " << PartOne(input) << endl;
  cout << "Part Two: " << PartTwo(input) << endl;

  return 0;
}
