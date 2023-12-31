#include <fstream>
#include <iostream>

#include "shared.h"

using namespace std;

vector<string> ReadLines(std::string file_path)
{
    vector<string> lines;
    ifstream file(file_path);

    if (!file.is_open()) {
        cerr << "Unable to open file: " << file_path << endl;
        exit(-1);
    }

    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    return lines;
}

string TrimString(const string &str)
{
    // From https://stackoverflow.com/a/1798170
    const auto strBegin = str.find_first_not_of(' ');
    if (strBegin == std::string::npos) {
        return ""; // no content
    }

    const auto strEnd = str.find_last_not_of(' ');
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

vector<string> SplitString(const string &str, char delimiter)
{
    // From https://stackoverflow.com/a/73446843
    std::vector<std::string> tokens;
    std::size_t start = 0, end = 0;
    while ((end = str.find(delimiter, start)) != std::string::npos) {
        auto substr = str.substr(start, end - start);
        if (!substr.empty()) {
            tokens.push_back(substr);
        }
        start = end + 1;
    }
    tokens.push_back(str.substr(start));
    return tokens;
}

CharMatrix::CharMatrix(vector<string> lines)
{
    for (string &line : lines) {
        vector<char> row;
        for (char &c : line) {
            row.push_back(c);
        }
        chars.push_back(row);
    }
}

char CharMatrix::CharAt(Point point) { return chars[point.y][point.x]; }

vector<Point> CharMatrix::NeighborPoints(Point point, bool include_diagonal)
{
    vector<Point> neighbors;

    vector<Point> possible_neighbor_points;
    if (include_diagonal) {
        possible_neighbor_points = {
            Point { point.x - 1, point.y - 1 },
            Point { point.x, point.y - 1 },
            Point { point.x + 1, point.y - 1 },

            Point { point.x - 1, point.y },
            Point { point.x + 1, point.y },

            Point { point.x - 1, point.y + 1 },
            Point { point.x, point.y + 1 },
            Point { point.x + 1, point.y + 1 },
        };
    } else {
        possible_neighbor_points = {
            Point { point.x, point.y - 1 },
            Point { point.x - 1, point.y },
            Point { point.x + 1, point.y },
            Point { point.x, point.y + 1 },
        };
    }

    for (auto &point : possible_neighbor_points) {
        if (point.x >= 0 && point.y < Width() && point.y >= 0 && point.y < Height()) {
            neighbors.push_back(point);
        }
    }

    return neighbors;
}

vector<char> CharMatrix::Neighbors(Point point, bool includeDiagonal)
{
    vector<char> neighbors;
    auto neighbor_points = NeighborPoints(point, includeDiagonal);
    for (auto &point : neighbor_points) {
        neighbors.push_back(chars[point.y][point.x]);
    }

    return neighbors;
}

void CharMatrix::Print()
{
    for (auto &row : chars) {
        for (auto &c : row) {
            cout << c;
        }
        cout << endl;
    }
}