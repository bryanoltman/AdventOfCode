#include <cstddef>
#include <iostream>
#include <map>
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
    if (regex_match(line, match, broadcaster_regex)) {
      mod.name = "broadcaster";
      destinations = SplitString(match[1].str(), ',');
    }
    else if (regex_match(line, match, module_regex)) {
      auto type = match[1].str();
      if (type == "%") {
        mod.is_flip_flop = true;
      }
      else if (type == "&") {
        mod.is_conjunction = true;
      }
      else {
        cerr << "Unknown module type: " << type << endl;
        exit(-1);
      }

      mod.name = match[2].str();
      destinations = SplitString(match[1].str(), ',');
    }
    else {
      cout << "Unknown line: " << line << endl;
    }

    for (auto &dest : destinations) {
      mod.destinations.push_back(TrimString(dest));
    }

    modules[mod.name] = mod;
  }

  return modules;
}

size_t PartOne(Input input)
{
  size_t ret = 0;
  return ret;
}

size_t PartTwo(Input input)
{
  size_t ret = 0;
  return ret;
}