#ifndef _2023_20_20_H_
#define _2023_20_20_H_

#include <map>
#include <string>

using namespace std;

struct Module {
  string name;

  vector<string> destinations;

  bool is_on;

  // Flip-flop modules a prefixed with a '%'
  // If it receives a high pulse, it does nothing.
  // If it receives a low pulse, it switches on or off.
  // If it was off, it sends a high pulse.
  // If it was on, it sends a low pulse.
  bool is_flip_flop;

  // Conjunction modules are prefixed with a '&'
  // They remember the last pulse from all inputs, defaulting to a "low" pulse.
  // If it remembers a high pulse from all inputs, it sends a low pulse.
  // If it remembers a low pulse from any input, it sends a low pulse.
  bool is_conjunction;

  // Only used for conjunction modules.
  unordered_map<string, bool> inputs;
};

typedef unordered_map<string, Module> Input;

Input ParseInput(const string &filename);

size_t PartOne(Input input);
size_t PartTwo(Input input);

#endif // _2023_20_20_H_