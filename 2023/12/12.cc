#include <cstddef>
#include <iostream>

#include "12/12.h"
#include "shared/shared.h"

using namespace std;

Input ParseInput(const string &filename) {
  auto ret = vector<SpringRecord>();
  auto lines = ReadLines(filename);
  for (auto &line : lines) {
    auto parts = SplitString(line, ' ');
    auto spring = parts[0];
    auto condition = parts[1];
    auto condition_parts = SplitString(condition, ',');
    auto arrangement = vector<size_t>();
    for (auto &part : condition_parts) {
      arrangement.push_back(stoi(part));
    }
    ret.push_back({spring, arrangement});
  }
  return ret;
}

bool SpringMatchesArrangement(string spring, vector<size_t> arrangement) {
  auto current_spring_length = 0;
  auto arrangement_index = 0;
  for (auto &c : spring) {
    if (c == '#') {
      current_spring_length++;
    } else if (current_spring_length != 0) {
      if (arrangement[arrangement_index] != current_spring_length) {
        return false;
      }
      arrangement_index++;
      current_spring_length = 0;
    }
  }

  if (arrangement_index < arrangement.size() - 1) {
    return false;
  } else if (arrangement_index == arrangement.size() - 1) {
    return current_spring_length == arrangement[arrangement_index];
  } else if (arrangement_index == arrangement.size()) {
    return current_spring_length == 0;
  }

  return false;
}

size_t NumPossibleStrings(string spring, vector<size_t> arrangement) {
  vector<string> springs = {""};
  for (auto &c : spring) {
    vector<string> new_springs;
    for (auto &spring : springs) {
      if (c == '?') {
        new_springs.push_back(spring + '#');
        new_springs.push_back(spring + '.');
      } else {
        new_springs.push_back(spring + c);
      }
    }

    springs = new_springs;
  }

  size_t ret = 0;
  for (auto &s : springs) {
    if (SpringMatchesArrangement(s, arrangement)) {
      ret++;
    }
  }
  return ret;
}

size_t PartOne(Input input) {
  size_t ret = 0;
  for (auto &record : input) {
    auto num_possible =
        NumPossibleStrings(record.spring_condition, record.arrangement);
    ret += num_possible;
  }
  return ret;
}

size_t PartTwo(Input input) { return 0; }