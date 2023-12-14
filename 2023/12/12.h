#ifndef _2023_12_12_H_
#define _2023_12_12_H_

#include <string>

using namespace std;

struct SpringRecord {
  string spring_condition;
  vector<size_t> arrangement;
};

typedef vector<SpringRecord> Input;

Input ParseInput(const string &filename);

bool SpringMatchesArrangement(string spring, vector<size_t> arrangement);
size_t NumPossibleStrings(string spring, vector<size_t> arrangement);

size_t PartOne(Input input);
size_t PartTwo(Input input);

#endif // _2023_12_12_H_