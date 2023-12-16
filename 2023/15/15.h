#ifndef _2023_15_15_H_
#define _2023_15_15_H_

#include <string>

using namespace std;

typedef vector<string> Input;

struct Instruction {
    char op;
    string label;
    size_t power;
};

struct Lens {
    string label;
    size_t power;
};

Input ParseInput(const string &filename);
Instruction InstructionFromString(const string &str);

size_t Hash(const string &str);

size_t PartOne(Input input);
size_t PartTwo(Input input);

#endif // _2023_15_15_H_