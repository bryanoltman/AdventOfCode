#ifndef SHARED_H
#define SHARED_H

#include <string>
#include <vector>

using namespace std;

vector<string> ReadLines(string file_path);

vector<string> SplitString(const string &str, char delimiter);

string TrimString(const std::string &line);

struct Point {
  int x;
  int y;

  static Point Add(Point a, Point b) { return a + b; }

  Point operator+(const Point &other) const
  {
    return {x + other.x, y + other.y};
  }

  Point operator-(const Point &other) const
  {
    return {x - other.x, y - other.y};
  }

  bool operator==(const Point &other) const
  {
    return x == other.x && y == other.y;
  }

  // Implement < for use in std::set
  bool operator<(const Point &other) const
  {
    return x < other.x || (x == other.x && y < other.y);
  }
};

const Point UP = {0, -1};
const Point DOWN = {0, 1};
const Point LEFT = {-1, 0};
const Point RIGHT = {1, 0};

class CharMatrix {
public:
  CharMatrix(vector<string> lines);
  vector<Point> NeighborPoints(Point point, bool include_diagonal = true);
  vector<char> Neighbors(Point point, bool include_diagonal = true);
  vector<vector<char>> chars;
  char CharAt(Point point);

  size_t Height() const { return chars.size(); }

  size_t Width() const
  {
    if (chars.empty()) {
      return 0;
    }
    return chars[0].size();
  }

  bool ContainsPoint(Point point)
  {
    return point.x >= 0 && point.y >= 0 && point.x < Width() &&
           point.y < Height();
  }

  void Print();
};

#endif // SHARED_H