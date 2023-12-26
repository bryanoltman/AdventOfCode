#ifndef _2023_25_25_H_
#define _2023_25_25_H_

#include <map>
#include <string>

using namespace std;

struct Component {
  string name;
  vector<string> linked_components;
};

typedef unordered_map<string, Component> Input;

Input ParseInput(const string &filename);

size_t PartOne(Input input);
size_t PartTwo(Input input);

#endif // _2023_25_25_H_