#include <cstddef>
#include <iostream>
#include <regex>
#include <vector>

#include "shared/shared.h"

using namespace std;

struct Range {
    Range(size_t start, size_t length)
    {
        this->start = start;
        this->end = start + length;
        this->length = length;
    }

    size_t start;
    size_t end;
    size_t length;
};

struct SourceDestRanges {
    Range source_range;
    Range dest_range;
};

struct SourceDestMap {
    string source_name;
    string dest_name;
    vector<SourceDestRanges> ranges;

    void Print();
};

struct Input {
    vector<size_t> seeds;
    vector<SourceDestMap> maps;
};

void SourceDestMap::Print()
{
    cout << source_name << " to " << dest_name << endl;
    for (auto &range : ranges) {
        cout << "  " << range.dest_range.start << " " << range.source_range.start << " "
             << range.source_range.length << endl;
    }
}

vector<size_t> ReadSeedsLine(const string &line)
{
    auto seed_numbers_str = line.substr(sizeof(("seeds: ")));
    cout << "seed_numbers_str: " << seed_numbers_str << endl;
    auto seed_numbers = SplitString(seed_numbers_str, ' ');
    vector<size_t> ret;
    for (auto &seed_number : seed_numbers) {
        cout << "seed_number: " << seed_number << endl;
        ret.push_back(stoi(seed_number));
    }
    return ret;
}

SourceDestRanges ReadSourceDestRangesLine(const string &line)
{
    static auto ranges_regex = regex(R"R((\d+) (\d+) (\d+))R");

    smatch matches;
    regex_match(line, matches, ranges_regex);

    auto dest_start = stoi(matches[1].str());
    auto source_start = stoi(matches[2].str());
    auto length = stoi(matches[3].str());

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

int main(int argc, char const *argv[])
{
    // auto input = ParseInput("inputs/05.txt");
    auto input = ParseInput("inputs/05.test.txt");

    cout << "Seeds: ";
    for (auto seed : input.seeds) {
        cout << seed << " ";
    }
    cout << endl;

    cout << "Maps:" << endl;
    for (auto &map : input.maps) {
        map.Print();
    }

    // cout << "Part One: " << PartOne(input) << endl;
    // cout << "Part Two: " << PartTwo(input) << endl;

    return 0;
}
