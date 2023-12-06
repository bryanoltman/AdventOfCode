#include <iostream>
#include <regex>

#include "05.h"

using namespace std;

void SourceDestMap::Print() const
{
    cout << source_name << " to " << dest_name << endl;
    for (auto &range : ranges) {
        cout << "  " << range.dest_range.start << " " << range.source_range.start << " "
             << range.source_range.length << endl;
    }
}

size_t SourceDestMap::DestValue(size_t source) const
{
    for (auto &range : ranges) {
        if (range.source_range.Contains(source)) {
            auto offset = source - range.source_range.start;
            return offset + range.dest_range.start;
        }
    }
    return source;
}

vector<size_t> ReadSeedsLine(const string &line)
{
    auto seed_numbers_str = line.substr(sizeof(("seeds:")));
    cout << "seed_numbers_str: " << seed_numbers_str << endl;
    auto seed_numbers = SplitString(seed_numbers_str, ' ');
    vector<size_t> ret;
    for (auto &seed_number : seed_numbers) {
        cout << "seed_number: " << seed_number << endl;
        ret.push_back(stol(seed_number));
    }
    return ret;
}

SourceDestRanges ReadSourceDestRangesLine(const string &line)
{
    static auto ranges_regex = regex(R"R((\d+) (\d+) (\d+))R");

    smatch matches;
    regex_match(line, matches, ranges_regex);

    auto dest_start = stol(matches[1].str());
    auto source_start = stol(matches[2].str());
    auto length = stol(matches[3].str());

    return SourceDestRanges { Range(source_start, length), Range(dest_start, length) };
}

SourceDestMap ReadMapLines(vector<string> lines, vector<string>::iterator &lines_iter)
{
    static auto map_name_regex = regex(R"R(^(\w+)-to-(\w+) map:$)R");

    SourceDestMap ret;
    auto name_line = *lines_iter;
    lines_iter++;

    smatch name_matches;
    regex_match(name_line, name_matches, map_name_regex);
    ret.source_name = name_matches[1].str();
    ret.dest_name = name_matches[2].str();

    for (; lines_iter != lines.end(); lines_iter++) {
        auto line = *lines_iter;
        cout << "line is " << line << endl;
        if (line.empty()) {
            break;
        }
        ret.ranges.push_back(ReadSourceDestRangesLine(line));
    }

    return ret;
}

Input ParseInput(const string &filename)
{
    auto lines = ReadLines(filename);

    Input ret;
    auto lines_iter = lines.begin();
    ret.seeds = ReadSeedsLine(*lines_iter++);

    do {
        // Skip the blank line
        lines_iter++;
        ret.maps.push_back(ReadMapLines(lines, lines_iter));
    } while (lines_iter != lines.end());

    return ret;
}

size_t PartOne(const Input &input)
{
    auto first_map = input.maps[0];
    vector<size_t> location_numbers;
    for (auto &seed : input.seeds) {
        cout << endl;
        size_t current_val = seed;
        for (auto &map : input.maps) {
            current_val = map.DestValue(current_val);
        }

        location_numbers.push_back(current_val);
    }

    size_t min_location_value = location_numbers[0];
    for (auto &location_number : location_numbers) {
        if (location_number < min_location_value) {
            min_location_value = location_number;
        }
    }

    return min_location_value;
}
