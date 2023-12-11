#ifndef _2023_10_10_H_
#define _2023_10_10_H_

#include <string>

#include "shared/shared.h"

using namespace std;

typedef CharMatrix Input;

Input ParseInput(const string &filename);

size_t PartOne(Input input);
size_t PartTwo(Input input);

#endif // _2023_10_10_H_