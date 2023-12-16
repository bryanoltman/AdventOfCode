#ifndef _2023_14_14_H_
#define _2023_14_14_H_

#include <string>

#include "shared/shared.h"

using namespace std;

typedef CharMatrix Input;

Input ParseInput(const string &filename);

CharMatrix ApplyTilt(CharMatrix &matrix);

size_t PartOne(Input input);
size_t PartTwo(Input input);

#endif // _2023_14_14_H_