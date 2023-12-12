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

    // cout << "num_empty_rows_crossed: " << num_empty_rows_crossed << endl;
    // cout << "num_empty_cols_crossed: " << num_empty_cols_crossed << endl;

    return x_diff + y_diff + num_empty_cols_crossed + num_empty_rows_crossed;
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
    // cout << "Part One" << endl;
    auto empty_cols = EmptyColumns(input);
    auto empty_rows = EmptyRows(input);

    // cout << "empty_cols: ";
    // for (auto col : empty_cols) {
    //     cout << col << " ";
    // }
    // cout << endl;

    // cout << "empty_rows: ";
    // for (auto row : empty_rows) {
    //     cout << row << " ";
    // }
    // cout << endl;

    auto galaxies = FindGalaxies(input);
    size_t total_distance = 0;
    for (int i = 0; i < galaxies.size() - 1; i++) {
        auto a = galaxies[i];
        for (int j = i + 1; j < galaxies.size(); j++) {
            auto b = galaxies[j];
            auto distance = DistanceBetweenGalaxies(input, a, b, empty_rows, empty_cols);
            // cout << "Distance between " << a.first << "," << a.second << " and " << b.first <<
            // ","
            //      << b.second << " is " << distance << endl;
            total_distance += distance;
        }

        // cout << endl;
    }

    return total_distance;
}

size_t PartTwo(Input input) { return 0; }
