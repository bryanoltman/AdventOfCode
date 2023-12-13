#include <cstddef>
#include <iostream>

#include "12/12.h"
#include "shared/shared.h"

using namespace std;

Input ParseInput(const string &filename)
{
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
        ret.push_back({ spring, arrangement });
    }
    return ret;
}

bool SpringMatchesArrangement(string spring, vector<size_t> arrangement)
{
    cout << endl;
    size_t arrangement_index = 0;
    size_t current_spring_length = 0;
    bool is_in_spring = false;
    for (char c : spring) {
        if (c == '#') {
            if (arrangement_index >= arrangement.size() && !is_in_spring) {
                return false;
            }
            is_in_spring = true;
            current_spring_length++;
        } else if (c == '.') {
            if (is_in_spring) {
                if (arrangement[arrangement_index] != current_spring_length) {
                    return false;
                }
                arrangement_index++;
            }
            is_in_spring = false;
            current_spring_length = 0;
        } else {
            cerr << "Unexpected character in spring: " << c << endl;
            exit(1);
        }
    }

    if (is_in_spring && current_spring_length != arrangement[arrangement_index]) {
        return false;
    }

    return true;
}

size_t PartOne(Input input) { return 0; }

size_t PartTwo(Input input) { return 0; }