#include <cstddef>
#include <iostream>

#include "11/11.h"
#include "shared/shared.h"

using namespace std;

Input ParseInput(const string &filename)
{
    auto lines = ReadLines(filename);
    auto matrix = CharMatrix(lines);
    return matrix;
}

vector<pair<long, long>> FindGalaxies(const Input &input)
{
    vector<pair<long, long>> ret;
    for (auto y = 0; y < input.Height(); y++) {
        for (auto x = 0; x < input.Width(); x++) {
            if (input.chars[y][x] == '#') {
                ret.push_back(make_pair(x, y));
            }
        }
    }

    return ret;
}

size_t DistanceBetweenGalaxies(const Input &input, const pair<long, long> &a,
    const pair<long, long> &b, set<long> &empty_rows, set<long> &empty_cols)
{
    long x_diff = abs(b.first - a.first);
    long y_diff = abs(b.second - a.second);

    size_t num_empty_rows_crossed = 0;
    for (auto row : empty_rows) {
        if ((row > a.second && row < b.second) || (row > b.second && row < a.second)) {
            num_empty_rows_crossed++;
        }
    }

    size_t num_empty_cols_crossed = 0;
    for (auto col : empty_cols) {
        if ((col > a.first && col < b.first) || (col > b.first && col < a.first)) {
            num_empty_cols_crossed++;
        }
    }

    return x_diff + y_diff + num_empty_cols_crossed + num_empty_rows_crossed;
}

size_t DistanceBetweenGalaxiesPart2(const Input &input, const pair<long, long> &a,
    const pair<long, long> &b, set<long> &empty_rows, set<long> &empty_cols)
{
    long empty_multiplier = 1000000;
    size_t num_empty_rows_crossed = 0;
    for (auto row : empty_rows) {
        if ((row > a.second && row < b.second) || (row > b.second && row < a.second)) {
            num_empty_rows_crossed++;
        }
    }

    size_t num_empty_cols_crossed = 0;
    for (auto col : empty_cols) {
        if ((col > a.first && col < b.first) || (col > b.first && col < a.first)) {
            num_empty_cols_crossed++;
        }
    }

    long x_diff = abs(b.first - a.first) + (num_empty_cols_crossed * (empty_multiplier - 1));
    long y_diff = abs(b.second - a.second) + (num_empty_rows_crossed * (empty_multiplier - 1));

    return x_diff + y_diff;
}

set<long> EmptyRows(const Input &input)
{
    set<long> ret;
    for (auto y = 0; y < input.Height(); y++) {
        bool is_empty = true;
        for (auto x = 0; x < input.Width(); x++) {
            if (input.chars[y][x] == '#') {
                is_empty = false;
                break;
            }
        }
        if (is_empty) {
            ret.insert(y);
        }
    }
    return ret;
}

set<long> EmptyColumns(const Input &input)
{
    set<long> ret;
    for (auto x = 0; x < input.Width(); x++) {
        bool is_empty = true;
        for (auto y = 0; y < input.Height(); y++) {
            if (input.chars[y][x] == '#') {
                is_empty = false;
                break;
            }
        }

        if (is_empty) {
            ret.insert(x);
        }
    }
    return ret;
}

size_t PartOne(Input input)
{
    auto empty_cols = EmptyColumns(input);
    auto empty_rows = EmptyRows(input);
    auto galaxies = FindGalaxies(input);
    size_t total_distance = 0;
    for (int i = 0; i < galaxies.size() - 1; i++) {
        auto a = galaxies[i];
        for (int j = i + 1; j < galaxies.size(); j++) {
            auto b = galaxies[j];
            auto distance = DistanceBetweenGalaxies(input, a, b, empty_rows, empty_cols);
            total_distance += distance;
        }
    }

    return total_distance;
}

size_t PartTwo(Input input)
{
    auto empty_cols = EmptyColumns(input);
    auto empty_rows = EmptyRows(input);
    auto galaxies = FindGalaxies(input);
    size_t total_distance = 0;
    for (int i = 0; i < galaxies.size() - 1; i++) {
        auto a = galaxies[i];
        for (int j = i + 1; j < galaxies.size(); j++) {
            auto b = galaxies[j];
            auto distance = DistanceBetweenGalaxiesPart2(input, a, b, empty_rows, empty_cols);
            total_distance += distance;
        }
    }

    return total_distance;
}
