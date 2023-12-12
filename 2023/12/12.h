#ifndef _2023_12_12_H_
#define _2023_12_12_H_

#include <set>
#include <string>

#include "shared/shared.h"

using namespace std;

typedef vector<string> Input;

Input ParseInput(const string &filename);

size_t PartOne(Input input);
size_t PartTwo(Input input);

#endif // _2023_12_12_H_