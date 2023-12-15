#include <cstddef>
#include <iostream>
#include <map>

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

SpringRecord UnfoldRecord(SpringRecord record) {
  SpringRecord ret;
  for (int i = 0; i < 5; i++) {
    ret.spring_condition += record.spring_condition;
    if (i != 4) {
      ret.spring_condition += '?';
    }
    ret.arrangement.insert(ret.arrangement.end(), record.arrangement.begin(),
                           record.arrangement.end());
  }

  return ret;
}

// A huge amount of thanks to
// https://www.reddit.com/r/adventofcode/comments/18ge41g/comment/kd93dvp/?utm_source=share&utm_medium=web2x&context=3
// for the example.
size_t MemoizedNumPossibleStrings(string spring, vector<size_t> arrangement) {
  string states_str = ".";
  for (auto &length : arrangement) {
    for (int i = 0; i < length; i++) {
      states_str += '#';
    }
    states_str += '.';
  }

  map<size_t, size_t> states_counts = {{0, 1}};
  map<size_t, size_t> next_states;
  for (auto &c : spring) {
    for (auto &pair : states_counts) {
      auto state_index = pair.first;
      auto state_count = pair.second;

      // We can move to the next state if
      // 1. There is a next state to move to, and
      // 2. The current state is a wildcard ('?') or matches the next state
      //    (states_str[i + 1])
      //
      // We also still can conform to the target arrangement if the current
      // state is a wildcard ('?') or a '.', as the '#' characters are allowed
      // to have an arbitrary amount of '.'s between them.
      bool has_next_state = state_index + 1 < states_str.size();
      switch (c) {
      case '?':
        if (has_next_state) {
          next_states[state_index + 1] =
              next_states[state_index + 1] + states_counts[state_index];
        }
        if (states_str[state_index] == '.') {
          next_states[state_index] =
              next_states[state_index] + states_counts[state_index];
        }
        break;
      case '.':
        if (has_next_state && states_str[state_index + 1] == '.') {
          next_states[state_index + 1] =
              next_states[state_index + 1] + state_count;
        }
        if (states_str[state_index] == '.') {
          next_states[state_index] =
              next_states[state_index] + states_counts[state_index];
        }
        break;
      case '#':
        if (has_next_state && states_str[state_index + 1] == '#') {
          next_states[state_index + 1] =
              next_states[state_index + 1] + states_counts[state_index];
        }
        break;
      }
    }

    states_counts = next_states;
    next_states = {};
  }

  return states_counts[states_str.size() - 1] +
         states_counts[states_str.size() - 2];
}

size_t PartOne(Input input) {
  size_t ret = 0;
  for (auto &record : input) {
    auto num_possible =
        MemoizedNumPossibleStrings(record.spring_condition, record.arrangement);
    ret += num_possible;
  }
  return ret;
}

size_t PartTwo(Input input) {
  size_t ret = 0;
  for (auto &record : input) {
    auto unfolded = UnfoldRecord(record);
    auto num_possible = MemoizedNumPossibleStrings(unfolded.spring_condition,
                                                   unfolded.arrangement);
    ret += num_possible;
  }
  return ret;
}