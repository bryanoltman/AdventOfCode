#ifndef _2023_18_18_H_
#define _2023_18_18_H_

#include <string>

#include "shared/shared.h"

using namespace std;

struct Dig {
    Point direction;
    int distance;
    int color;
};

typedef vector<Dig> Input;

Input ParseInput(const string &filename);

size_t PartOne(Input input);
size_t PartTwo(Input input);

#endif // _2023_18_18_H_