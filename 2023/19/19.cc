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
      // cout << "line: " << line << endl;
      regex_match(line, match, workflow_regex);
      Workflow workflow;
      auto workflow_name = match[1].str();
      auto rules_str = match[2].str();
      auto rules = SplitString(rules_str, ',');
      for (auto &rule_str : rules) {
        // cout << "rule_str: " << rule_str << endl;
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
      // cout << "workflow name: \"" << workflow_name << "\"" << endl;
      // for (auto &rule : workflow.rules) {
      //   cout << "rule: " << rule.parameter << " " << rule.gt << " " <<
      //   rule.cmp
      //        << " " << rule.result << endl;
      // }
      ret.workflows[workflow_name] = workflow;
    }
    else {
      // cout << endl;
      // cout << "line: " << line << endl;
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
    // cout << endl;
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

size_t PartTwo(Input input)
{
  size_t ret = 0;
  return ret;
}