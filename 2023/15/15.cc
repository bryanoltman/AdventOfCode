#include <cstddef>

#include "15/15.h"
#include "shared/shared.h"

using namespace std;

Input ParseInput(const string &filename)
{
    auto line = ReadLines(filename)[0];
    return SplitString(line, ',');
}

size_t Hash(const string &str)
{
    size_t ret = 0;
    for (auto &c : str) {
        ret += c;
        ret *= 17;
        ret %= 256;
    }
    return ret;
}

size_t PartOne(Input input)
{
    size_t ret = 0;
    for (auto &item : input) {
        ret += Hash(item);
    }
    return ret;
}

size_t PartTwo(Input input)
{
    size_t ret = 0;
    return ret;
}