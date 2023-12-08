#ifndef _2023_08_08_H_
#define _2023_08_08_H_

#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Input {
  string directions;
  unordered_map<string, pair<string, string>> nodes;
};

Input ParseInput(const string &filename);

size_t PartOne(Input input);
size_t PartTwo(Input input);

#endif // _2023_08_08_H_