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

vector<vector<size_t>> Derivatives(const vector<size_t> &numbers)
{
    vector<vector<size_t>> ret;
    ret.push_back(numbers);
    auto current_numbers = numbers;
    while (true) {
        vector<size_t> derivative;
        for (size_t i = 0; i < current_numbers.size() - 1; i++) {
            auto current = current_numbers[i];
            auto next = current_numbers[i + 1];
            derivative.push_back(next - current);
        }
        ret.push_back(derivative);
        current_numbers = derivative;

        auto first_nonzero
            = find_if(derivative.begin(), derivative.end(), [](size_t n) { return n != 0; });
        if (first_nonzero == derivative.end()) {
            break;
        }
    }

    return ret;
}

size_t NextNumberInSequence(const vector<size_t> &numbers)
{
    auto d = Derivatives(numbers);
    size_t next_number = 0;
    for (int i = d.size() - 1; i >= 0; i--) {
        next_number += d[i].back();
    }
    return next_number;
}

size_t PartOne(Input input)
{
    size_t ret = 0;
    for (auto i = 0; i < input.size(); i++) {
        ret += NextNumberInSequence(input[i]);
    }

    return ret;
}

size_t PartTwo(Input input) { return 0; }
