#include <cstddef>
#include <iostream>
#include <set>

#include "16/16.h"

using namespace std;

Point UP = { 0, -1 };
Point DOWN = { 0, 1 };
Point LEFT = { -1, 0 };
Point RIGHT = { 1, 0 };

struct Beam {
    Point pos;
    Point dir;

    // Define a comparison operator for Beam
    bool operator<(const Beam &other) const
    {
        // Compare the position first
        if (pos.x < other.pos.x)
            return true;
        if (pos.x > other.pos.x)
            return false;

        // If positions are equal, compare the y values
        if (pos.y < other.pos.y)
            return true;
        if (pos.y > other.pos.y)
            return false;

        // If positions are equal, compare the direction
        if (dir.x < other.dir.x)
            return true;
        if (dir.x > other.dir.x)
            return false;

        // If directions are equal, compare the y values
        return dir.y < other.dir.y;
    }
};

Input ParseInput(const string &filename)
{
    auto lines = ReadLines(filename);
    return CharMatrix(lines);
}

size_t PointsCovered(Input input, Beam beam)
{
    vector<Beam> beams = { beam };
    set<Beam> visited = {};
    while (!beams.empty()) {
        auto current = beams.back();
        beams.pop_back();
        if (!input.ContainsPoint(current.pos)) {
            // If this point is outside the map, we don't need to visit it.
            continue;
        }
        if (visited.find(current) != visited.end()) {
            // If we've already been in this position moving in this direction,
            // we don't need to visit it again.
            continue;
        }

        visited.insert(current);

        char current_char = input.CharAt({ current.pos.x, current.pos.y });
        if (current_char == '.') {
            beams.push_back({ Point::Add(current.pos, current.dir), current.dir });
        } else if (current_char == '|') {
            if (current.dir == UP || current.dir == DOWN) {
                // Moving up or down, continue in same direction
                beams.push_back({ Point::Add(current.pos, current.dir), current.dir });
            } else {
                // Moving left or right
                beams.push_back({ Point::Add(current.pos, UP), UP });
                beams.push_back({ Point::Add(current.pos, DOWN), DOWN });
            }
        } else if (current_char == '-') {
            if (current.dir == RIGHT || current.dir == LEFT) {
                beams.push_back({ Point::Add(current.pos, current.dir), current.dir });
            } else {
                // Moving up or down
                beams.push_back({ Point::Add(current.pos, LEFT), LEFT });
                beams.push_back({ Point::Add(current.pos, RIGHT), RIGHT });
            }
        } else if (current_char == '/') {
            if (current.dir == RIGHT) {
                beams.push_back({ Point::Add(current.pos, UP), UP });
            } else if (current.dir == LEFT) {
                beams.push_back({ Point::Add(current.pos, DOWN), DOWN });
            } else if (current.dir == UP) {
                beams.push_back({ Point::Add(current.pos, RIGHT), RIGHT });
            } else if (current.dir == DOWN) {
                beams.push_back({ Point::Add(current.pos, LEFT), LEFT });
            }
        } else if (current_char == '\\') {
            if (current.dir == RIGHT) {
                beams.push_back({ Point::Add(current.pos, DOWN), DOWN });
            } else if (current.dir == LEFT) {
                beams.push_back({ Point::Add(current.pos, UP), UP });
            } else if (current.dir == UP) {
                beams.push_back({ Point::Add(current.pos, LEFT), LEFT });
            } else if (current.dir == DOWN) {
                beams.push_back({ Point::Add(current.pos, RIGHT), RIGHT });
            }
        }
    }

    set<Point> visited_points = {};
    for (auto beam : visited) {
        visited_points.insert(beam.pos);
    }

    return visited_points.size();
}

size_t PartOne(Input input)
{
    // We start at 0,0 moving right
    return PointsCovered(input, { { 0, 0 }, RIGHT });
}

size_t PartTwo(Input input)
{
    size_t ret = 0;
    for (int y = 0; y < input.Height(); y++) {
        auto x = 0;
        if (input.CharAt({ x, y }) == '.') {
            size_t points_covered = PointsCovered(input, { { x, y }, RIGHT });
            if (points_covered > ret) {
                ret = points_covered;
            }
        }
        x = input.Width() - 1;
        if (input.CharAt({ x, y }) == '.') {
            size_t points_covered = PointsCovered(input, { { x, y }, LEFT });
            if (points_covered > ret) {
                ret = points_covered;
            }
        }
    }

    for (int x = 0; x < input.Width(); x++) {
        auto y = 0;
        if (input.CharAt({ x, y }) == '.') {
            size_t points_covered = PointsCovered(input, { { x, y }, DOWN });
            if (points_covered > ret) {
                ret = points_covered;
            }
        }
        y = input.Height() - 1;
        if (input.CharAt({ x, y }) == '.') {
            size_t points_covered = PointsCovered(input, { { x, y }, UP });
            if (points_covered > ret) {
                ret = points_covered;
            }
        }
    }

    return ret;
}