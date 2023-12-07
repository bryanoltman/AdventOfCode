#include <iostream>

#include "06/06.h"

using namespace std;

int main(int argc, char const *argv[]) {
  Input part_one_input = {
      {50, 242},  //
      {74, 1017}, //
      {86, 1691}, //
      {85, 1252}  //
  };

  Input part_two_input = {{50748685, 242101716911252}};

  cout << "Part One: " << PartOne(part_one_input) << endl;
  cout << "Part Two: " << PartTwo(part_two_input) << endl;

  return 0;
}
