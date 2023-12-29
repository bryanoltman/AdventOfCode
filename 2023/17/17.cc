#include <cstddef>
#include <iostream>
#include <map>
#include <set>

#include "17/17.h"
#include "shared/shared.h"

using namespace std;

Input ParseInput(const string &filename)
{
  auto lines = ReadLines(filename);
  return CharMatrix(lines);
}

map<Point, size_t> dijkstra(CharMatrix matrix, Point start)
{
  map<Point, size_t> distances = {};
  set<Point> unvisited_points = {};
  for (int y = 0; y < matrix.Height(); y++) {
    for (int x = 0; x < matrix.Width(); x++) {
      distances[{x, y}] = numeric_limits<size_t>::max();
      unvisited_points.insert({x, y});
    }
  }

  distances[start] = 0;
  auto current_point = start;
  while (!unvisited_points.empty()) {
    auto current_point_dist = distances[current_point];
    auto neighbors = matrix.NeighborPoints(current_point);
    for (auto &neighbor : neighbors) {
      if (unvisited_points.find(neighbor) == unvisited_points.end()) {
        continue;
      }

      auto neighbor_dist = distances[neighbor];
      auto neighbor_char = matrix.CharAt({neighbor.x, neighbor.y});
      auto neighbor_digit = neighbor_char - '0';
      if (current_point_dist + neighbor_digit < neighbor_dist) {
        distances[neighbor] = current_point_dist + neighbor_digit;
      }
    }

    cout << "removing " << current_point.x << ", " << current_point.y << endl;
    cout << "unvisited_points.size() = " << unvisited_points.size() << endl;
    cout << endl;
    unvisited_points.erase(current_point);

    Point next_point = *unvisited_points.begin();
    for (auto &point : unvisited_points) {
      if (distances[point] < distances[next_point]) {
        next_point = point;
      }
    }
    current_point = next_point;
  }

  return distances;
}

size_t PartOne(Input input)
{
  auto point_distances = dijkstra(input, {0, 0});
  for (auto &pair : point_distances) {
    cout << pair.first.x << ", " << pair.first.y << " = " << pair.second
         << endl;
  }

  return point_distances[{
      static_cast<int>(input.Width() - 1), //
      static_cast<int>(input.Height() - 1) //
  }];
}

size_t PartTwo(Input input)
{
  size_t ret = 0;
  return ret;
}