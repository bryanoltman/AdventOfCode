#include <cstddef>
#include <map>

#include "15/15.h"
#include "shared/shared.h"

using namespace std;

Input ParseInput(const string &filename)
{
    auto line = ReadLines(filename)[0];
    return SplitString(line, ',');
}

Instruction InstructionFromString(const string &str)
{
    Instruction ret;
    for (auto &c : str) {
        if (c == '=' || c == '-') {
            ret.op = c;
            break;
        }
        ret.label += c;
    }

    if (ret.op == '=') {
        auto parts = SplitString(str, '=');
        ret.power = stoi(parts[1]);
    } else {
        ret.power = 0;
    }

    return ret;
}

size_t Hash(const string &str)
{
    size_t ret = 0;
    for (auto &c : str) {
        ret += c;
        ret *= 17;
        ret %= 256;
    }
    return ret;
}

size_t PartOne(Input input)
{
    size_t ret = 0;
    for (auto &item : input) {
        ret += Hash(item);
    }
    return ret;
}

size_t PartTwo(Input input)
{
    size_t ret = 0;
    map<size_t, vector<Lens>> boxes;
    for (auto &item : input) {
        auto instruction = InstructionFromString(item);
        auto box_number = Hash(instruction.label);
        auto box = boxes[box_number];
        auto lens_location = find_if(
            box.begin(), box.end(), [&](Lens &lens) { return lens.label == instruction.label; });
        switch (instruction.op) {
        case '=':
            if (lens_location == box.end()) {
                box.push_back({ instruction.label, instruction.power });
            } else {
                lens_location->power = instruction.power;
            }
            break;
        case '-':
            if (lens_location != box.end()) {
                box.erase(lens_location);
            }

            break;
        }

        boxes[box_number] = box;
    }

    for (auto &numbered_box : boxes) {
        size_t box_value = 0;
        auto box_number = numbered_box.first;
        auto box = numbered_box.second;
        for (auto i = 0; i < box.size(); i++) {
            auto lens = box[i];
            box_value += (box_number + 1) * lens.power * (i + 1);
        }

        ret += box_value;
    }

    return ret;
}