#include <cstddef>
#include <iostream>
#include <map>

#include "25/25.h"
#include "shared/shared.h"

using namespace std;

Input ParseInput(const string &filename)
{
  auto lines = ReadLines(filename);
  Input ret;
  for (auto line : lines) {
    auto parts = SplitString(line, ':');
    auto name = parts[0];
    auto linked_components = SplitString(parts[1], ' ');
    ret[name] = {name, linked_components};
  }
  return ret;
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