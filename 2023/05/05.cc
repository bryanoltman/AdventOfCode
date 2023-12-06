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
    auto seed_numbers = SplitString(seed_numbers_str, ' ');
    vector<size_t> ret;
    for (auto &seed_number : seed_numbers) {
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

    return SourceDestRanges { Range(source_start, source_start + length),
        Range(dest_start, dest_start + length) };
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

size_t PartOne(const Input &input)
{
    size_t min_location = SIZE_T_MAX;
    for (auto &seed : input.seeds) {
        size_t current_val = seed;
        for (auto &map : input.maps) {
            current_val = map.DestValue(current_val);
        }

        if (current_val < min_location) {
            min_location = current_val;
        }
    }

    return min_location;
}

size_t PartTwo(const Input &input)
{
    vector<Range> current_seed_ranges;
    for (auto seeds_itr = input.seeds.begin(); seeds_itr != input.seeds.end();) {
        auto seed = *seeds_itr++;
        auto length = *seeds_itr++;
        auto seed_range = Range(seed, length);
        current_seed_ranges.push_back(seed_range);
    }

    for (auto &map : input.maps) {
        // Translate each seed range as per the source-destination maps

        vector<Range> new_seed_ranges;
        while (!current_seed_ranges.empty()) {
            auto seed_range = current_seed_ranges.back();
            current_seed_ranges.pop_back();

            auto start = seed_range.start;
            auto end = seed_range.end;

            bool found_overlap = false;

            for (auto &map_range : map.ranges) {
                auto max_start = max(start, map_range.source_range.start);
                auto min_end = min(end, map_range.source_range.end);

                auto source_start = map_range.source_range.start;
                auto dest_start = map_range.dest_range.start;

                // seed: 55-68
                // map:  50-98

                if (max_start < min_end) {
                    // The current seed range overlaps with this source-destination range
                    found_overlap = true;

                    // Add the area of overlap to the next round of seed ranges
                    auto new_range_start = max_start - source_start + dest_start;
                    auto new_range_end = min_end - source_start + dest_start;
                    new_seed_ranges.push_back(Range(new_range_start, new_range_end));

                    if (max_start > seed_range.start) {
                        // If we overlapped in the beginning of the range, add the seed range up
                        // until the beginning of the overlap
                        current_seed_ranges.push_back(Range(seed_range.start, max_start));
                    }

                    if (min_end < seed_range.end) {
                        // If we overlapped at the end of the range, add the seed range from the end
                        // of the overlap to the end of the seed range.
                        current_seed_ranges.push_back(Range(min_end, seed_range.end));
                    }

                    break;
                }
            }

            if (!found_overlap) {
                // If we didn't find any overlap, add the entire seed range to the next round of
                // seed ranges.
                new_seed_ranges.push_back(seed_range);
            }
        }

        current_seed_ranges = new_seed_ranges;
    }

    // At this point, our seed ranges have all become location ranges. Take the lowest start of all
    // of them.
    size_t min_location = SIZE_T_MAX;
    for (auto &seed_range : current_seed_ranges) {
        if (seed_range.start < min_location) {
            min_location = seed_range.start;
        }
    }

    return min_location;
}