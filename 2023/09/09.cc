#include <cstddef>
#include <iostream>

#include "09/09.h"
#include "shared/shared.h"

using namespace std;

Input ParseInput(const string &filename)
{
    Input ret;
    auto lines = ReadLines(filename);
    for (auto &line : lines) {
        auto number_strs = SplitString(line, ' ');
        vector<size_t> numbers;
        for (auto str : number_strs) {
            numbers.push_back(stoi(str));
        }
        ret.push_back(numbers);
    }

    return ret;
}

size_t PartOne(Input input) { return 0; }

size_t PartTwo(Input input) { return 0; }
