#ifndef _2023_19_19_H_
#define _2023_19_19_H_

#include <map>
#include <string>

using namespace std;

struct Rule {
  char parameter; // x, m, a, s
  bool gt;        // if false, lt
  unsigned long cmp;
  string result; // either a value or a rule name
};

struct Workflow {
  string name;
  vector<Rule> rules;
};

struct Part {
  int x;
  int m;
  int a;
  int s;
};

struct Input {
  map<string, Workflow> workflows;
  vector<Part> parts;
};

Input ParseInput(const string &filename);

size_t PartOne(Input input);
size_t PartTwo(Input input);

#endif // _2023_19_19_H_