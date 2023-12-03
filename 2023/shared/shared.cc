#include "shared.h"

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

vector<pair<int, int>> CharMatrix::NeighborPoints(int x, int y, bool include_diagonal)
{
    vector<pair<int, int>> neighbors;
    if (x - 1 >= 0 && y - 1 >= 0 && include_diagonal) {
        neighbors.push_back(make_pair(x - 1, y - 1));
    }
    if (x - 1 >= 0) {
        neighbors.push_back(make_pair(x - 1, y));
    }
    if (x - 1 >= 0 && y + 1 < Height() && include_diagonal) {
        neighbors.push_back(make_pair(x - 1, y + 1));
    }
    if (y - 1 >= 0) {
        neighbors.push_back(make_pair(x, y - 1));
    }
    if (y + 1 < Height()) {
        neighbors.push_back(make_pair(x, y + 1));
    }
    if (x + 1 < Width() && y - 1 >= 0 && include_diagonal) {
        neighbors.push_back(make_pair(x + 1, y - 1));
    }
    if (x + 1 < Width()) {
        neighbors.push_back(make_pair(x + 1, y));
    }
    if (x + 1 < Width() && y + 1 < Height() && include_diagonal) {
        neighbors.push_back(make_pair(x + 1, y + 1));
    }

    return neighbors;
}

vector<char> CharMatrix::Neighbors(int x, int y, bool includeDiagonal)
{
    vector<char> neighbors;
    auto neighbor_points = NeighborPoints(x, y, includeDiagonal);
    for (auto &point : neighbor_points) {
        neighbors.push_back(chars[point.second][point.first]);
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