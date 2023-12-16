#ifndef _2023_13_13_H_
#define _2023_13_13_H_

#include <string>

#include "shared/shared.h"

using namespace std;

typedef vector<CharMatrix> Input;

Input ParseInput(const string &filename);

vector<size_t> VerticalReflectionIndex(CharMatrix &matrix);
vector<size_t> HorizontalReflectionIndex(CharMatrix &matrix);

size_t PartOne(Input input);
size_t PartTwo(Input input);

#endif // _2023_13_13_H_