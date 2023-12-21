#include <cstddef>
#include <iostream>
#include <map>
#include <regex>

#include "19/19.h"
#include "shared/shared.h"

using namespace std;

Input ParseInput(const string &filename)
{
  regex workflow_regex(R"((\w+)\{(.+)\})");
  regex rule_regex(R"((\w)([>|<])(.+):(.+))");
  regex part_regex(R"(\{x=(\d+),m=(\d+),a=(\d+),s=(\d+)\})");
  auto lines = ReadLines(filename);

  Input ret;
  bool in_rules = true;
  for (auto &line : lines) {
    if (line.empty()) {
      in_rules = false;
      continue;
    }

    smatch match;
    if (in_rules) {
      regex_match(line, match, workflow_regex);
      Workflow workflow;
      auto workflow_name = match[1].str();
      auto rules_str = match[2].str();
      auto rules = SplitString(rules_str, ',');
      for (auto &rule_str : rules) {
        regex_match(rule_str, match, rule_regex);
        Rule rule;
        if (!match.empty()) {
          rule.parameter = match[1].str()[0];
          rule.gt = match[2].str() == ">";
          rule.cmp = stoi(match[3].str());
          rule.result = match[4].str();
        }
        else {
          rule.parameter = 'x';
          rule.gt = true;
          rule.cmp = 0;
          rule.result = rule_str;
        }
        workflow.rules.push_back(rule);
      }
      ret.workflows[workflow_name] = workflow;
    }
    else {
      smatch match;
      bool has_match = regex_match(line, match, part_regex);
      if (!has_match) {
        cerr << "no match for " << line << endl;
        exit(-1);
      }
      Part part;
      part.x = stoi(match[1].str());
      part.m = stoi(match[2].str());
      part.a = stoi(match[3].str());
      part.s = stoi(match[4].str());
      ret.parts.push_back(part);
    }
  }
  return ret;
}

int ValueForParameter(Part &part, char parameter)
{
  switch (parameter) {
  case 'x':
    return part.x;
  case 'm':
    return part.m;
  case 'a':
    return part.a;
  case 's':
    return part.s;
  }

  cerr << "Unknown parameter: " << parameter << endl;
  exit(-1);
}

bool DoesRuleMatch(Rule &rule, Part &part)
{
  auto value = ValueForParameter(part, rule.parameter);
  if (rule.gt) {
    return value > rule.cmp;
  }
  else {
    return value < rule.cmp;
  }

  cerr << "Unknown parameter: " << rule.parameter << endl;
  exit(-1);
}

bool IsPartAccepted(Input &input, Part &part)
{
  string next = "in";
  while (next != "R" && next != "A") {
    auto workflow = input.workflows[next];
    for (auto &rule : workflow.rules) {
      if (DoesRuleMatch(rule, part)) {
        next = rule.result;
        break;
      }
    }
  }

  if (next == "R") {
    return false;
  }
  else if (next == "A") {
    return true;
  }

  cerr << "Unknown next: " << next << endl;
  exit(-1);
}

size_t PartOne(Input input)
{
  size_t ret = 0;
  for (auto &part : input.parts) {
    if (IsPartAccepted(input, part)) {
      ret += part.x + part.m + part.a + part.s;
    }
  }
  return ret;
}

struct PartRange {
  unsigned long min_x;
  unsigned long max_x;
  unsigned long min_m;
  unsigned long max_m;
  unsigned long min_a;
  unsigned long max_a;
  unsigned long min_s;
  unsigned long max_s;
};

pair<PartRange, PartRange> SplitRangeOnRule(PartRange range, Rule rule)
{
  auto accepted = range;
  auto filtered = range;
  switch (rule.parameter) {
  case 'x':
    if (rule.gt) {
      accepted.min_x = max(accepted.min_x, rule.cmp + 1);
      filtered.max_x = min(filtered.max_x, rule.cmp);
    }
    else {
      accepted.max_x = min(accepted.max_x, rule.cmp - 1);
      filtered.min_x = max(filtered.min_x, rule.cmp);
    }
    break;
  case 'm':
    if (rule.gt) {
      accepted.min_m = max(accepted.min_m, rule.cmp + 1);
      filtered.max_m = min(filtered.max_m, rule.cmp);
    }
    else {
      accepted.max_m = min(accepted.max_m, rule.cmp - 1);
      filtered.min_m = max(filtered.min_m, rule.cmp);
    }
    break;
  case 'a':
    if (rule.gt) {
      accepted.min_a = max(accepted.min_a, rule.cmp + 1);
      filtered.max_a = min(filtered.max_a, rule.cmp);
    }
    else {
      accepted.max_a = min(accepted.max_a, rule.cmp - 1);
      filtered.min_a = max(filtered.min_a, rule.cmp);
    }

    break;
  case 's':
    if (rule.gt) {
      accepted.min_s = max(accepted.min_s, rule.cmp + 1);
      filtered.max_s = min(filtered.max_s, rule.cmp);
    }
    else {
      accepted.max_s = min(accepted.max_s, rule.cmp - 1);
      filtered.min_s = max(filtered.min_s, rule.cmp);
    }
    break;
  default:
    cerr << "Unknown parameter: " << rule.parameter << endl;
    exit(-1);
  }

  return {accepted, filtered};
}

size_t PartTwo(Input input)
{
  vector<pair<string, PartRange>> range_states;
  range_states.push_back({
      "in",
      {1, 4000, 1, 4000, 1, 4000, 1, 4000},
  });
  vector<PartRange> accepted_part_ranges;
  while (!range_states.empty()) {
    auto range_state = range_states.back();
    range_states.pop_back();
    auto workflow = input.workflows[range_state.first];
    auto remaining_range = range_state.second;
    for (auto &rule : workflow.rules) {
      auto split = SplitRangeOnRule(remaining_range, rule);
      auto accepted = split.first;
      remaining_range = split.second;
      if (rule.result == "A") {
        accepted_part_ranges.push_back(accepted);
      }
      else if (rule.result == "R") {
        // do nothing
        continue;
      }
      else {
        range_states.push_back({rule.result, accepted});
      }
    }
  }

  size_t ret = 0;

  for (auto &range : accepted_part_ranges) {
    auto x_range_width = range.max_x - range.min_x + 1;
    auto m_range_width = range.max_m - range.min_m + 1;
    auto a_range_width = range.max_a - range.min_a + 1;
    auto s_range_width = range.max_s - range.min_s + 1;
    ret += (x_range_width * m_range_width * a_range_width * s_range_width);
  }

  return ret;
}