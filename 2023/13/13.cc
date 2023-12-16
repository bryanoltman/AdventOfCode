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

optional<size_t> VerticalReflectionIndex(CharMatrix &matrix, size_t num_diffs)
{
    for (size_t vert_idx = 1; vert_idx < matrix.Width(); vert_idx++) {
        size_t diffs = 0;
        for (size_t y = 0; y < matrix.Height(); y++) {
            int left = vert_idx - 1;
            auto right = vert_idx;
            while (left >= 0 && right < matrix.Width()) {
                auto left_char = matrix.CharAt({ left, y });
                auto right_char = matrix.CharAt({ right, y });
                if (left_char != right_char) {
                    diffs++;
                }
                right++;
                left--;
            }

            if (diffs > num_diffs) {
                break;
            }
        }

        if (diffs == num_diffs) {
            return vert_idx;
        }
    }

    return nullopt;
}

optional<size_t> HorizontalReflectionIndex(CharMatrix &matrix, size_t num_diffs)
{
    for (size_t horiz_idx = 1; horiz_idx < matrix.Height(); horiz_idx++) {
        size_t diffs = 0;
        for (size_t x = 0; x < matrix.Width(); x++) {
            int top = horiz_idx - 1;
            auto bottom = horiz_idx;
            while (top >= 0 && bottom < matrix.Height()) {
                auto top_char = matrix.CharAt({ x, top });
                auto bottom_char = matrix.CharAt({ x, bottom });
                if (top_char != bottom_char) {

                    diffs++;
                }
                bottom++;
                top--;
            }

            if (diffs > num_diffs) {
                break;
            }
        }

        if (diffs == num_diffs) {
            return horiz_idx;
        }
    }

    return nullopt;
}

size_t PartOne(Input input)
{
    size_t ret = 0;
    for (auto &matrix : input) {
        auto horizontal = HorizontalReflectionIndex(matrix, 0);
        if (horizontal.has_value()) {
            ret += horizontal.value() * 100;
        }

        auto vertical = VerticalReflectionIndex(matrix, 0);
        if (vertical.has_value()) {
            ret += vertical.value();
        }
    }

    return ret;
}

size_t PartTwo(Input input)
{
    size_t ret = 0;
    for (auto &matrix : input) {
        auto horizontal = HorizontalReflectionIndex(matrix, 1);
        if (horizontal.has_value()) {
            ret += horizontal.value() * 100;
        }

        auto vertical = VerticalReflectionIndex(matrix, 1);
        if (vertical.has_value()) {
            ret += vertical.value();
        }
    }

    return ret;
}