#include <cstddef>
#include <iostream>

#include "13/13.h"
#include "shared/shared.h"

using namespace std;

Input ParseInput(const string &filename)
{
    auto lines = ReadLines(filename);
    vector<CharMatrix> ret;
    vector<string> current_lines;
    for (auto &line : lines) {
        if (line.empty()) {
            ret.push_back(CharMatrix(current_lines));
            current_lines = {};
            continue;
        }
        current_lines.push_back(line);
    }

    if (current_lines.size() > 0) {
        ret.push_back(CharMatrix(current_lines));
    }

    return ret;
}

vector<size_t> VerticalReflectionIndex(CharMatrix &matrix)
{
    vector<size_t> ret;
    for (size_t vert_idx = 1; vert_idx < matrix.Width(); vert_idx++) {
        bool has_symmetry = true;
        for (size_t y = 0; y < matrix.Height(); y++) {
            int left = vert_idx - 1;
            auto right = vert_idx;
            while (left >= 0 && right < matrix.Width()) {
                auto left_char = matrix.CharAt({ left, y });
                auto right_char = matrix.CharAt({ right, y });
                if (left_char != right_char) {
                    has_symmetry = false;
                    break;
                }
                right++;
                left--;
            }

            if (!has_symmetry) {
                break;
            }
        }

        if (has_symmetry) {
            ret.push_back(vert_idx);
        }
    }

    return ret;
}

vector<size_t> HorizontalReflectionIndex(CharMatrix &matrix)
{
    vector<size_t> ret;
    for (size_t horiz_idx = 1; horiz_idx < matrix.Height(); horiz_idx++) {
        bool has_symmetry = true;
        for (size_t x = 0; x < matrix.Width(); x++) {
            int top = horiz_idx - 1;
            auto bottom = horiz_idx;
            while (top >= 0 && bottom < matrix.Height()) {
                auto top_char = matrix.CharAt({ x, top });
                auto bottom_char = matrix.CharAt({ x, bottom });
                if (top_char != bottom_char) {
                    has_symmetry = false;
                    break;
                }
                bottom++;
                top--;
            }

            if (!has_symmetry) {
                break;
            }
        }

        if (has_symmetry) {
            ret.push_back(horiz_idx);
        }
    }

    return ret;
}

size_t PartOne(Input input)
{
    size_t ret = 0;
    for (auto &matrix : input) {

        auto horizontals = HorizontalReflectionIndex(matrix);
        for (auto &idx : horizontals) {
            ret += idx * 100;
        }

        auto verticals = VerticalReflectionIndex(matrix);
        for (auto &idx : verticals) {
            ret += idx;
        }
    }

    return ret;
}

size_t PartTwo(Input input)
{
    size_t ret = 0;
    return ret;
}