#include <cstddef>
#include <iostream>
#include <map>
#include <queue>
#include <regex>

#include "20/20.h"
#include "shared/shared.h"

using namespace std;

Input ParseInput(const string &filename)
{
  smatch match;
  auto broadcaster_regex = regex(R"(broadcaster -> (.+))");
  auto module_regex = regex(R"(([%|&])(\w+) -> (.+))");
  auto lines = ReadLines(filename);
  unordered_map<string, Module> modules;
  for (auto &line : lines) {
    vector<string> destinations;
    Module mod;
    mod.is_on = false;
    if (regex_match(line, match, broadcaster_regex)) {
      mod.name = "broadcaster";
      destinations = SplitString(match[1].str(), ',');
    }
    else if (regex_match(line, match, module_regex)) {
      auto type = match[1].str();
      if (type == "%") {
        mod.is_conjunction = false;
        mod.is_flip_flop = true;
      }
      else if (type == "&") {
        mod.is_flip_flop = false;
        mod.is_conjunction = true;
      }
      else {
        cerr << "Unknown module type: " << type << endl;
        exit(-1);
      }

      mod.name = match[2].str();
      destinations = SplitString(match[3].str(), ',');
    }
    else {
      cerr << "Unknown line: " << line << endl;
      exit(-1);
    }

    for (auto &dest : destinations) {
      mod.destinations.push_back(TrimString(dest));
    }

    modules[mod.name] = mod;
  }

  for (auto &mod : modules) {
    for (auto &dest : mod.second.destinations) {
      modules[dest].inputs[mod.first] = false;
    }
  }

  return modules;
}

// Returns the number of high and low pulses sent.
pair<size_t, size_t> PushButton(Input &input)
{
  pair<size_t, size_t> ret = {0, 0};
  // source, dest, is_high_pulse
  queue<tuple<string, string, bool>> pulses;
  Module &broadcaster = input["broadcaster"];

  ret.second++;

  for (auto &dest : broadcaster.destinations) {
    pulses.push({broadcaster.name, dest, false});
  }

  while (!pulses.empty()) {
    auto pulse = pulses.front();
    pulses.pop();

    auto source_name = get<0>(pulse);
    auto dest_name = get<1>(pulse);
    auto is_high_pulse = get<2>(pulse);

    if (is_high_pulse) {
      ret.first++;
    }
    else {
      ret.second++;
    }

    auto &dest = input[dest_name];
    if (dest.is_flip_flop) {
      if (is_high_pulse) {
        continue;
      }

      bool is_sending_high_pulse = !dest.is_on;
      for (auto &new_dest : dest.destinations) {
        pulses.push({dest_name, new_dest, is_sending_high_pulse});
      }
      dest.is_on = !dest.is_on;
    }
    else {
      // mod is conjunction
      dest.inputs[source_name] = is_high_pulse;
      bool are_all_inputs_high = true;
      for (auto &input : dest.inputs) {
        if (!input.second) {
          are_all_inputs_high = false;
          break;
        }
      }

      bool is_sending_high_pulse = !are_all_inputs_high;
      for (auto &new_dest : dest.destinations) {
        pulses.push({dest_name, new_dest, is_sending_high_pulse});
      }
    }
  }

  return ret;
}

// Returns true if a low pulse was sent to module 'rx'.
bool PushButtonPartTwo(Input &input)
{
  // source, dest, is_high_pulse
  queue<tuple<string, string, bool>> pulses;
  Module &broadcaster = input["broadcaster"];

  for (auto &dest : broadcaster.destinations) {
    pulses.push({broadcaster.name, dest, false});
  }

  while (!pulses.empty()) {
    auto pulse = pulses.front();
    pulses.pop();

    auto source_name = get<0>(pulse);
    auto dest_name = get<1>(pulse);
    auto is_high_pulse = get<2>(pulse);

    if (dest_name == "rx" && !is_high_pulse) {
      return true;
    }

    auto &dest = input[dest_name];
    if (dest.is_flip_flop) {
      if (is_high_pulse) {
        continue;
      }

      bool is_sending_high_pulse = !dest.is_on;
      for (auto &new_dest : dest.destinations) {
        pulses.push({dest_name, new_dest, is_sending_high_pulse});
      }
      dest.is_on = !dest.is_on;
    }
    else {
      // mod is conjunction
      dest.inputs[source_name] = is_high_pulse;
      bool are_all_inputs_high = true;
      for (auto &input : dest.inputs) {
        if (!input.second) {
          are_all_inputs_high = false;
          break;
        }
      }

      bool is_sending_high_pulse = !are_all_inputs_high;
      for (auto &new_dest : dest.destinations) {
        pulses.push({dest_name, new_dest, is_sending_high_pulse});
      }
    }
  }

  return false;
}

size_t PartOne(Input input)
{
  pair<size_t, size_t> ret = {0, 0};
  for (int i = 0; i < 1000; i++) {
    auto pulses = PushButton(input);
    ret.first += pulses.first;
    ret.second += pulses.second;
  }

  return ret.first * ret.second;
}

size_t PartTwo(Input input)
{
  int presses = 1;
  while (!PushButtonPartTwo(input)) {
    presses++;
    if (presses % 1000 == 0) {
      cout << "Presses: " << presses << endl;
    }
  }
  return presses;
}