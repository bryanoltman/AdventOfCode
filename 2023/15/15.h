#ifndef _2023_15_15_H_
#define _2023_15_15_H_

#include <string>

using namespace std;

typedef vector<string> Input;

Input ParseInput(const string &filename);

size_t Hash(const string &str);

size_t PartOne(Input input);
size_t PartTwo(Input input);

#endif // _2023_15_15_H_