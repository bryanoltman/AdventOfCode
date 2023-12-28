#include <cstddef>
#include <iostream>
#include <map>

#include "23/23.h"
#include "shared/shared.h"

using namespace std;

Input ParseInput(const string &filename)
{
  auto lines = ReadLines(filename);
  return CharMatrix(lines);
}

vector<vector<Point>> AllPaths(CharMatrix &input)
{
  Point start = {1, 0};
  Point end = {static_cast<int>(input.Width() - 2),
               static_cast<int>(input.Height() - 1)};
  vector<vector<Point>> closed_paths;
  vector<vector<Point>> open_paths;
  open_paths.push_back({start});
  while (!open_paths.empty()) {
    auto current_path = open_paths.back();
    open_paths.pop_back();
    auto last_point = current_path.back();
    if (last_point == end) {
      closed_paths.push_back(current_path);
      continue;
    }

    auto current_char = input.CharAt(last_point);
    if (current_char == '.') {
      auto neighbors = input.NeighborPoints(last_point, false);
      for (auto neighbor : neighbors) {
        auto neighbor_char = input.CharAt(neighbor);
        if (neighbor_char == '#') {
          continue;
        }

        if (find(current_path.begin(), current_path.end(), neighbor) !=
            current_path.end()) {
          continue;
        }

        auto new_path = current_path;
        new_path.push_back(neighbor);
        open_paths.push_back(new_path);
      }
      continue;
    }

    Point next_point;

    if (current_char == '>') {
      next_point = last_point + RIGHT;
    }
    else if (current_char == '<') {
      next_point = last_point + RIGHT;
    }
    else if (current_char == '^') {
      next_point = last_point + RIGHT;
    }
    else if (current_char == 'v') {
      next_point = last_point + DOWN;
    }

    auto next_char = input.CharAt(next_point);
    if (next_char == '#') {
      continue;
    }

    if (find(current_path.begin(), current_path.end(), next_point) !=
        current_path.end()) {
      continue;
    }

    auto new_path = current_path;
    new_path.push_back(next_point);
    open_paths.push_back(new_path);
  }

  return closed_paths;
}

size_t PartOne(Input input)
{
  auto all_paths = AllPaths(input);
  size_t ret = 0;
  for (auto &path : all_paths) {
    if (path.size() > ret) {
      ret = path.size();
    }
  }

  // Don't include the start point as a step
  return ret - 1;
}

size_t PartTwo(Input input)
{
  for (auto y = 0; y < input.Height(); y++) {
    for (auto x = 0; x < input.Width(); x++) {
      if (input.CharAt({x, y}) != '#') {
        input.chars[y][x] = '.';
      }
    }
  }
  auto all_paths = AllPaths(input);
  size_t ret = 0;
  for (auto &path : all_paths) {
    if (path.size() > ret) {
      ret = path.size();
    }
  }

  // Don't include the start point as a step
  return ret - 1;
}