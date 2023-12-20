#include <cstddef>
#include <iostream>
#include <regex>
#include <set>

#include "18/18.h"
#include "shared/shared.h"

using namespace std;

Input ParseInput(const string &filename)
{
  auto lines = ReadLines(filename);
  auto dig_regex = regex(R"(([R|L|U|D]) (\d+) \(#(\w+)\))");
  vector<Dig> ret;
  for (auto &line : lines) {
    smatch match;
    regex_match(line, match, dig_regex);
    string direction_str = match[1].str();
    char direction_char = match[1].str()[0];
    int distance = stoi(match[2].str());
    string color_str = match[3].str();
    // cout << direction_char << "   " << distance << " " << color_str <<
    // endl;
    ret.push_back({
        {
            direction_char == 'R'   ? RIGHT //
            : direction_char == 'D' ? DOWN  //
            : direction_char == 'L' ? LEFT  //
                                    : UP,   //
        },
        distance,              //
        stoi(color_str, 0, 16) //
    });
    // cout << ret.back().direction.x << "," << ret.back().direction.y << " "
    //      << ret.back().distance << " " << ret.back().color << endl;
    // cout << endl;
  }

  return ret;
}

set<Point> BorderPoints(Input input)
{
  set<Point> ret;
  Point current = {0, 0};
  for (auto &dig : input) {
    for (int i = 0; i < dig.distance; i++) {
      current = Point::Add(current, dig.direction);
      ret.insert(current);
    }
  }
  return ret;
}

CharMatrix DrawDig(set<Point> points)
{
  int min_x = 0;
  int max_x = 0;
  int min_y = 0;
  int max_y = 0;

  for (auto &point : points) {
    if (point.x < min_x) {
      min_x = point.x;
    }
    if (point.x > max_x) {
      max_x = point.x;
    }
    if (point.y < min_y) {
      min_y = point.y;
    }
    if (point.y > max_y) {
      max_y = point.y;
    }
  }

  CharMatrix ret = CharMatrix({});
  for (int y = min_y; y <= max_y; y++) {
    vector<char> row;
    for (int x = min_x; x <= max_x; x++) {
      auto point = Point{x, y};
      if (find(points.begin(), points.end(), point) != points.end()) {
        row.push_back('#');
      }
      else {
        row.push_back('.');
      }
    }

    ret.chars.push_back(row);
  }

  return ret;
}

set<Point> PointsInLava(set<Point> border_points)
{
  int min_x = 0;
  int max_x = 0;
  int min_y = 0;
  int max_y = 0;

  for (auto &point : border_points) {
    if (point.x < min_x) {
      min_x = point.x;
    }
    if (point.x > max_x) {
      max_x = point.x;
    }
    if (point.y < min_y) {
      min_y = point.y;
    }
    if (point.y > max_y) {
      max_y = point.y;
    }
  }

  set<Point> ret;
  for (int y = min_y; y < max_y; y++) {
    for (int x = min_x; x < max_x; x++) {
      auto point = Point{x, y};
      if (border_points.find(point) != border_points.end()) {
        // Border points aren't considered lava
        continue;
      }

      int num_crossings = 0;
      bool is_on_up_horizontal = false;   // entered through a L or J
      bool is_on_down_horizontal = false; // entered through a F or 7
      for (int curr_x = x + 1; curr_x <= max_x; curr_x++) {
        auto curr_point = Point{curr_x, y};
        if (border_points.find(curr_point) == border_points.end()) {
          // cout << "(" << curr_x << "," << y << ") is not a border point"
          //      << endl;
          // Not a border point
          continue;
        }

        auto up_neighbor = Point{curr_x, y - 1};
        auto down_neighbor = Point{curr_x, y + 1};
        auto left_neighbor = Point{curr_x - 1, y};
        auto right_neighbor = Point{curr_x + 1, y};
        bool is_horizontal =
            border_points.find(up_neighbor) == border_points.end() &&
            border_points.find(down_neighbor) == border_points.end();
        if (is_horizontal) {
          // cout << "(" << curr_x << "," << y << ") is horizontal" << endl;
          continue;
        }

        bool is_vertical =
            border_points.find(up_neighbor) != border_points.end() &&
            border_points.find(down_neighbor) != border_points.end();
        if (is_vertical) {
          // cout << "(" << curr_x << "," << y << ") is vertical" << endl;
          num_crossings++;
          continue;
        }

        bool is_up_horizontal = // L or J
            (border_points.find(up_neighbor) != border_points.end() &&
             border_points.find(right_neighbor) != border_points.end()) ||
            (border_points.find(left_neighbor) != border_points.end() &&
             border_points.find(down_neighbor) != border_points.end());
        // cout << "(" << curr_x << "," << y << ") is up horizontal" << endl;
        bool is_down_horizontal = // 7 or F
            (border_points.find(up_neighbor) != border_points.end() &&
             border_points.find(left_neighbor) != border_points.end()) ||
            (border_points.find(right_neighbor) != border_points.end() &&
             border_points.find(down_neighbor) != border_points.end());
        // cout << "(" << curr_x << "," << y << ") is down horizontal" << endl;
        if (is_up_horizontal) {
          if (is_on_down_horizontal) {
            num_crossings++;
            is_on_down_horizontal = false;
          }
          else {
            is_on_down_horizontal = true;
          }
        }

        if (is_down_horizontal) {
          if (is_on_up_horizontal) {
            num_crossings++;
            is_on_up_horizontal = false;
          }
          else {
            is_on_up_horizontal = true;
          }
        }
      }

      if (num_crossings % 2 == 1) {
        ret.insert(point);
      }
    }
  }
  return ret;
}

size_t PartOne(Input input)
{
  auto border_points = BorderPoints(input);
  cout << "border points: " << border_points.size() << endl;
  auto in_lava = PointsInLava(border_points);
  cout << "in lava: " << in_lava.size() << ":" << endl;
  // for (auto &point : in_lava) {
  //   cout << point.x << "," << point.y << endl;
  // }

  // DrawDig(border_points).Print();
  // cout << endl;
  // border_points.merge(in_lava);
  // DrawDig(border_points).Print();

  return in_lava.size() + border_points.size();
}

size_t PartTwo(Input input)
{
  // TODO: look into https://en.wikipedia.org/wiki/Shoelace_formula
  size_t ret = 0;
  return ret;
}