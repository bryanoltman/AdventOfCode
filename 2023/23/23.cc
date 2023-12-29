#include <cstddef>
#include <iostream>
#include <map>
#include <set>
#include <utility>

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

map<Point, vector<pair<Point, size_t>>> FindJunctionPoints(CharMatrix &input)
{
  Point start = {1, 0};
  vector<Point> junction_points = {start};
  for (auto y = 0; y < input.Height(); y++) {
    for (auto x = 0; x < input.Width(); x++) {
      auto c = input.CharAt({x, y});
      if (c == '#') {
        continue;
      }

      auto neighbors = input.NeighborPoints({x, y}, false);
      int dot_neighbors = 0;
      for (auto neighbor : neighbors) {
        if (input.CharAt(neighbor) == '.') {
          dot_neighbors++;
        }
      }

      if (dot_neighbors > 2) {
        junction_points.push_back({x, y});
      }
    }
  }
  Point end = {static_cast<int>(input.Width() - 2),
               static_cast<int>(input.Height() - 1)};
  junction_points.push_back(end);

  map<Point, vector<pair<Point, size_t>>> ret;
  for (auto point : junction_points) {
    set<Point> visited_points = {point};
    vector<pair<Point, size_t>> to_visit = {{point, 0}};
    while (!to_visit.empty()) {
      auto pair = to_visit.back();
      to_visit.pop_back();
      auto next_point = pair.first;
      auto distance = pair.second;

      char c = input.CharAt(next_point);
      if (c == '#') {
        continue;
      }

      auto next_point_neighbors = input.NeighborPoints(next_point, false);
      for (auto &neighbor : next_point_neighbors) {
        if (visited_points.find(neighbor) != visited_points.end()) {
          continue;
        }

        visited_points.insert(neighbor);

        if (find(junction_points.begin(), junction_points.end(), neighbor) !=
            junction_points.end()) {
          ret[point].push_back({neighbor, distance + 1});
        }
        else {
          to_visit.push_back({neighbor, distance + 1});
        }
      }
    }
  }

  return ret;
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
  Point start = {1, 0};
  Point end = {static_cast<int>(input.Width() - 2),
               static_cast<int>(input.Height() - 1)};

  for (auto y = 0; y < input.Height(); y++) {
    for (auto x = 0; x < input.Width(); x++) {
      if (input.CharAt({x, y}) != '#') {
        input.chars[y][x] = '.';
      }
    }
  }

  auto junction_map = FindJunctionPoints(input);
  size_t max_distance = 0;
  vector<vector<pair<Point, size_t>>> open_paths;
  for (auto &neighbor : junction_map[start]) {
    auto neighbor_point = neighbor.first;
    auto distance = neighbor.second;
    vector<pair<Point, size_t>> path = {{neighbor_point, distance}};
    open_paths.push_back(path);
  }

  while (!open_paths.empty()) {
    vector<pair<Point, size_t>> path = open_paths.back();
    open_paths.pop_back();
    pair<Point, size_t> current_pair = path.back();
    auto current_point = current_pair.first;
    auto current_distance = current_pair.second;

    if (current_point == end) {
      if (current_distance > max_distance) {
        max_distance = current_distance;
      }

      continue;
    }

    auto neighbors = junction_map[current_point];
    for (auto &neighbor : neighbors) {
      auto neighbor_point = neighbor.first;
      bool in_path = false;
      for (auto &p : path) {
        if (p.first == neighbor_point) {
          in_path = true;
          break;
        }
      }

      if (in_path) {
        continue;
      }

      auto distance = neighbor.second;
      auto new_path = path;
      new_path.push_back({neighbor_point, current_distance + distance});
      open_paths.push_back(new_path);
    }
  }

  return max_distance;
}