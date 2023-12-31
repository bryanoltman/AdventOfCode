#include <iostream>

#include "13/13.h"

using namespace std;

int main(int argc, char const *argv[]) {
  Input input = ParseInput("inputs/13.txt");

  cout << "Part One: " << PartOne(input) << endl;
  cout << "Part Two: " << PartTwo(input) << endl;

  return 0;
}
