#ifndef _2023_06_06_H_
#define _2023_06_06_H_

#include <cstddef>
#include <vector>

using namespace std;

struct Race {
  size_t duration;
  size_t distance;
};

typedef vector<Race> Input;

size_t PartOne(Input input);
size_t PartTwo(Input input);

#endif // _2023_06_06_H_