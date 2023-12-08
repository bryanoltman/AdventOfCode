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

size_t PartOne(Input input) {
  size_t num_steps = 0;
  size_t directions_index = 0;
  string current_node = "AAA";
  while (current_node != "ZZZ") {
    char current_direction = input.directions[directions_index];
    directions_index++;
    if (directions_index == input.directions.length()) {
      directions_index = 0;
    }

    auto node_pair = input.nodes[current_node];
    if (current_direction == 'L') {
      current_node = node_pair.first;
    } else if (current_direction == 'R') {
      current_node = node_pair.second;
    } else {
      cout << "Unknown direction found " << current_direction << endl;
      exit(-1);
    }

    num_steps++;
  }

  return num_steps;
}

bool PartTwoIsDone(vector<string> nodes) {
  for (auto node : nodes) {
    if (node.back() != 'Z') {
      return false;
    }
  }
  return true;
}

size_t PartTwo(Input input) {
  size_t num_steps = 0;
  size_t directions_index = 0;
  vector<string> current_nodes;
  for (auto node_entry : input.nodes) {
    auto node = node_entry.first;
    if (node.back() == 'A') {
      current_nodes.push_back(node);
    }
  }

  while (!PartTwoIsDone(current_nodes)) {
    char current_direction = input.directions[directions_index];
    directions_index++;
    if (directions_index == input.directions.length()) {
      directions_index = 0;
    }

    vector<string> new_nodes;
    for (auto node : current_nodes) {
      auto node_pair = input.nodes[node];
      if (current_direction == 'L') {
        new_nodes.push_back(node_pair.first);
      } else if (current_direction == 'R') {
        new_nodes.push_back(node_pair.second);
      } else {
        cout << "Unknown direction found " << current_direction << endl;
        exit(-1);
      }
    }

    current_nodes = new_nodes;
    num_steps++;
  }

  return num_steps;
}
