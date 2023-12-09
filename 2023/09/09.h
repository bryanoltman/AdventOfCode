#ifndef _2023_09_09_H_
#define _2023_09_09_H_

#include <cstddef>
#include <string>
#include <vector>

using namespace std;

typedef vector<vector<size_t>> Input;

Input ParseInput(const string &filename);

vector<vector<size_t>> Derivatives(const vector<size_t> &numbers);
size_t NextNumberInSequence(const vector<size_t> &numbers);
size_t PartOne(Input input);
size_t PartTwo(Input input);

#endif // _2023_09_09_H_