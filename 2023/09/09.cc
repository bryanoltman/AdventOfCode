#include <cstddef>

#include "09/09.h"
#include "shared/shared.h"

using namespace std;

Input ParseInput(const string &filename)
{
    Input ret;
    auto lines = ReadLines(filename);
    for (auto &line : lines) {
        auto number_strs = SplitString(line, ' ');
        vector<long> numbers;
        for (auto str : number_strs) {
            numbers.push_back(stoi(str));
        }
        ret.push_back(numbers);
    }

    return ret;
}

vector<vector<long>> Derivatives(const vector<long> &numbers)
{
    vector<vector<long>> ret;
    ret.push_back(numbers);
    auto current_numbers = numbers;
    while (true) {
        vector<long> derivative;
        for (int i = 0; i < current_numbers.size() - 1; i++) {
            auto current = current_numbers[i];
            auto next = current_numbers[i + 1];
            derivative.push_back(next - current);
        }
        ret.push_back(derivative);
        current_numbers = derivative;

        auto first_nonzero
            = find_if(derivative.begin(), derivative.end(), [](long n) { return n != 0; });
        if (first_nonzero == derivative.end()) {
            break;
        }
    }

    return ret;
}

long NextNumberInSequence(const vector<long> &numbers)
{
    auto d = Derivatives(numbers);
    size_t next_number = 0;
    for (int i = d.size() - 1; i >= 0; i--) {
        next_number += d[i].back();
    }
    return next_number;
}

long PrevNumberInSequence(const vector<long> &numbers)
{
    auto d = Derivatives(numbers);
    long prev_number = 0;
    for (int i = d.size() - 1; i >= 0; i--) {
        prev_number = d[i][0] - prev_number;
    }
    return prev_number;
}

long PartOne(Input input)
{
    long ret = 0;
    for (auto i = 0; i < input.size(); i++) {
        ret += NextNumberInSequence(input[i]);
    }

    return ret;
}

long PartTwo(Input input)
{
    long ret = 0;
    for (auto i = 0; i < input.size(); i++) {
        ret += PrevNumberInSequence(input[i]);
    }

    return ret;
}
