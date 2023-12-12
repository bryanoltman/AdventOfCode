#ifndef _2023_11_11_H_
#define _2023_11_11_H_

#include <set>
#include <string>

#include "shared/shared.h"

using namespace std;

typedef CharMatrix Input;

Input ParseInput(const string &filename);

vector<pair<long, long>> FindGalaxies(const Input &input);
size_t DistanceBetweenGalaxies(const Input &input, const pair<long, long> &a,
    const pair<long, long> &b, set<long> &empty_rows, set<long> &empty_cols);
size_t DistanceBetweenGalaxiesPart2(const Input &input, const pair<long, long> &a,
    const pair<long, long> &b, set<long> &empty_rows, set<long> &empty_cols);
set<long> EmptyRows(const Input &input);
set<long> EmptyColumns(const Input &input);

size_t PartOne(Input input);
size_t PartTwo(Input input);

#endif // _2023_11_11_H_