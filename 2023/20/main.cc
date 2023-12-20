#include <iostream>

#include "20/20.h"

using namespace std;

int main(int argc, char const *argv[])
{
  Input input = ParseInput("inputs/20.txt");

  cout << "Part One: " << PartOne(input) << endl;
  cout << "Part Two: " << PartTwo(input) << endl;

  return 0;
}
