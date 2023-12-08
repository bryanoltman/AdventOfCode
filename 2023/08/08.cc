#include <cstddef>
#include <iostream>
#include <regex>
#include <set>

#include "08/08.h"
#include "shared/shared.h"

using namespace std;

static auto node_line_regex = regex(R"R((\w\w\w) = \((\w\w\w), (\w\w\w)\))R");

Input ParseInput(const string &filename) {
  auto lines = ReadLines(filename);
  Input ret;

  auto lines_itr = lines.begin();
  ret.directions = *lines_itr++;
  lines_itr++; // Skip the blank line
  for (; lines_itr != lines.end(); lines_itr++) {
    smatch matches;
    regex_match(*lines_itr, matches, node_line_regex);
    string node = matches[1].str();
    string left = matches[2].str();
    string right = matches[3].str();
    ret.nodes[node] = make_pair(left, right);
  }

  return ret;
}

size_t PartOne(Input input) { return 0; }

size_t PartTwo(Input input) { return 0; }
