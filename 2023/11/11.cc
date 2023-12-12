#include <cstddef>

#include "11/11.h"
#include "shared/shared.h"

using namespace std;

Input ParseInput(const string &filename)
{
    auto lines = ReadLines(filename);
    auto matrix = CharMatrix(lines);
    return matrix;
}

size_t PartOne(Input input) { return 0; }

size_t PartTwo(Input input) { return 0; }
