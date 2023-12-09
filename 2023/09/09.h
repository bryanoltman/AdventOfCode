#ifndef _2023_09_09_H_
#define _2023_09_09_H_

#include <string>
#include <vector>

using namespace std;

typedef vector<vector<long>> Input;

Input ParseInput(const string &filename);

vector<vector<long>> Derivatives(const vector<long> &numbers);

long NextNumberInSequence(const vector<long> &numbers);
long PrevNumberInSequence(const vector<long> &numbers);

long PartOne(Input input);
long PartTwo(Input input);

#endif // _2023_09_09_H_