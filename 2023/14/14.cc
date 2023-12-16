#include <cstddef>
#include <set>

#include "14/14.h"
#include "shared/shared.h"

using namespace std;

enum Direction { UP, LEFT, DOWN, RIGHT };

Input ParseInput(const string &filename)
{
    auto lines = ReadLines(filename);
    return CharMatrix(lines);
}

CharMatrix TiltUp(CharMatrix &matrix)
{
    CharMatrix ret = matrix;
    for (int y = 0; y < ret.Height(); y++) {
        for (int x = 0; x < ret.Width(); x++) {
            auto c = ret.CharAt({ x, y });
            if (c != '.') {
                continue;
            }
            // Look downwards to find 'O'
            for (int y2 = y + 1; y2 < ret.Height(); y2++) {
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

CharMatrix TiltDown(CharMatrix &matrix)
{
    CharMatrix ret = matrix;
    for (int y = ret.Height() - 1; y >= 0; y--) {
        for (int x = 0; x < ret.Width(); x++) {
            auto c = ret.CharAt({ x, y });
            if (c != '.') {
                continue;
            }
            // Look upwards to find 'O'
            for (int y2 = y - 1; y2 >= 0; y2--) {
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

CharMatrix TiltRight(CharMatrix &matrix)
{
    CharMatrix ret = matrix;
    for (int y = 0; y < ret.Height(); y++) {
        for (int x = ret.Width() - 1; x >= 0; x--) {
            auto c = ret.CharAt({ x, y });
            if (c != '.') {
                continue;
            }
            // Look left to find 'O'
            for (int x2 = x - 1; x2 >= 0; x2--) {
                auto c2 = ret.CharAt({ x2, y });
                if (c2 == '#') {
                    break;
                }

                if (c2 == 'O') {
                    // if we find 'O', swap with the current position
                    ret.chars[y][x] = 'O';
                    ret.chars[y][x2] = '.';
                    break;
                }
            }
        }
    }

    return ret;
}

CharMatrix TiltLeft(CharMatrix &matrix)
{
    CharMatrix ret = matrix;
    for (int y = 0; y < ret.Height(); y++) {
        for (int x = 0; x < ret.Width(); x++) {
            auto c = ret.CharAt({ x, y });
            if (c != '.') {
                continue;
            }
            // Look right to find 'O'
            for (int x2 = x + 1; x2 < ret.Width(); x2++) {
                auto c2 = ret.CharAt({ x2, y });
                if (c2 == '#') {
                    break;
                }

                if (c2 == 'O') {
                    // if we find 'O', swap with the current position
                    ret.chars[y][x] = 'O';
                    ret.chars[y][x2] = '.';
                    break;
                }
            }
        }
    }

    return ret;
}

size_t ComputeLoad(CharMatrix matrix)
{
    auto ret = 0;
    for (size_t y = 0; y < matrix.Height(); y++) {
        for (size_t x = 0; x < matrix.Width(); x++) {
            if (matrix.CharAt({ x, y }) == 'O') {
                ret += matrix.Height() - y;
            }
        }
    }

    return ret;
}
size_t PartOne(Input input)
{
    size_t ret = 0;
    auto tilted = TiltUp(input);
    ret = ComputeLoad(tilted);
    return ret;
}

size_t PartTwo(Input input)
{
    set<vector<vector<char>>> seen_patterns;
    size_t i = 0;
    size_t cycle_start = 0;
    size_t cycle_length = 0;
    vector<vector<char>> first_cycle;
    CharMatrix current = input;
    size_t stop_index = 0;
    for (;; i++) {
        Direction direction = static_cast<Direction>(i % 4);
        switch (direction) {
        case UP:
            current = TiltUp(current);
            break;
        case DOWN:
            current = TiltDown(current);
            break;
        case LEFT:
            current = TiltLeft(current);
            break;
        case RIGHT:
            current = TiltRight(current);
            break;
        }

        if (seen_patterns.find(current.chars) != seen_patterns.end()) {
            if (cycle_start == 0) {
                first_cycle = current.chars;
                cycle_start = i;
            } else if (cycle_length == 0 && current.chars == first_cycle) {
                cycle_length = i - cycle_start;
                // We're computing the state after 1000000000 cycles, where a
                // cycle is 4 turns.
                auto turns_remaining = 4000000000 - i - 1;
                stop_index = i + (turns_remaining % cycle_length);
            }

            if (i == stop_index) {
                break;
            }
        } else {
            seen_patterns.insert(current.chars);
        }
    }

    return ComputeLoad(current);
}