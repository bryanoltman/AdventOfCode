#include <cstddef>

#include "14/14.h"
#include "shared/shared.h"

using namespace std;

Input ParseInput(const string &filename)
{
    auto lines = ReadLines(filename);
    return CharMatrix(lines);
}

// Tilts north
CharMatrix ApplyTilt(CharMatrix &matrix)
{
    CharMatrix ret = matrix;
    for (size_t y = 0; y < ret.Height(); y++) {
        for (size_t x = 0; x < ret.Width(); x++) {
            auto c = ret.CharAt({ x, y });
            if (c != '.') {
                continue;
            }
            // Look downwards to find 'O'
            for (size_t y2 = y + 1; y2 < ret.Height(); y2++) {
                auto c2 = ret.CharAt({ x, y2 });
                if (c2 == '#') {
                    break;
                }

                if (c2 == 'O') {
                    // if we find 'O', swap with the current position
                    ret.chars[y][x] = 'O';
                    ret.chars[y2][x] = '.';
                    break;
                }
            }
        }
    }

    return ret;
}

size_t PartOne(Input input)
{
    size_t ret = 0;
    auto tilted = ApplyTilt(input);
    for (size_t y = 0; y < tilted.Height(); y++) {
        for (size_t x = 0; x < tilted.Width(); x++) {
            if (tilted.CharAt({ x, y }) == 'O') {
                ret += tilted.Height() - y;
            }
        }
    }

    return ret;
}

size_t PartTwo(Input input)
{
    size_t ret = 0;
    return ret;
}