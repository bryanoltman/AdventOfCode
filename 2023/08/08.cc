#include <cstddef>
#include <iostream>
#include <numeric>
#include <regex>

#include "08/08.h"
#include "shared/shared.h"

using namespace std;

static auto node_line_regex = regex(R"R((\w\w\w) = \((\w\w\w), (\w\w\w)\))R");

Input ParseInput(const string &filename)
{
    auto lines = ReadLines(filename);
    Input ret;

    auto lines_itr = lines.begin();
    ret.directions = *lines_itr++;
    lines_itr++; // Skip the blank line
    for (; lines_itr != lines.end(); lines_itr++) {
        smatch matches;
        regex_match(*lines_itr, matches, node_line_regex);
        string node = matches[1].str();
        string left = matches[2].str();
        string right = matches[3].str();
        ret.nodes[node] = make_pair(left, right);
    }

    return ret;
}

size_t PartOne(Input input)
{
    size_t num_steps = 0;
    size_t directions_index = 0;
    string current_node = "AAA";
    while (current_node != "ZZZ") {
        char current_direction = input.directions[directions_index];
        directions_index++;
        if (directions_index == input.directions.length()) {
            directions_index = 0;
        }

        auto node_pair = input.nodes[current_node];
        if (current_direction == 'L') {
            current_node = node_pair.first;
        } else if (current_direction == 'R') {
            current_node = node_pair.second;
        } else {
            cout << "Unknown direction found " << current_direction << endl;
            exit(-1);
        }

        num_steps++;
    }

    return num_steps;
}

bool PartTwoIsEndNode(string node) { return node.back() == 'Z'; }

pair<size_t, size_t> FindPartTwoFirstMatchAndCycleSize(Input input, string start_node)
{
    size_t directions_index = 0;
    size_t node_matches = 0;
    string current_node = start_node;
    size_t steps = 0;
    size_t first_match = SIZE_T_MAX;
    vector<size_t> match_steps;
    // 5 is arbitrarily chosen to find a cycle
    while (node_matches < 5) {
        char current_direction = input.directions[directions_index];
        directions_index++;
        if (directions_index == input.directions.length()) {
            directions_index = 0;
        }

        auto node_pair = input.nodes[current_node];
        if (current_direction == 'L') {
            current_node = node_pair.first;
        } else if (current_direction == 'R') {
            current_node = node_pair.second;
        } else {
            cout << "Unknown direction found " << current_direction << endl;
            exit(-1);
        }

        if (PartTwoIsEndNode(current_node)) {
            if (first_match == SIZE_T_MAX) {
                first_match = steps;
            }
            node_matches++;
            match_steps.push_back(steps);
        }

        steps++;
    }

    return make_pair(first_match, match_steps[4] - match_steps[3]);
}

// Returns LCM of array elements
// Adapted from https://www.geeksforgeeks.org/lcm-of-given-array-elements/
size_t findlcm(vector<size_t> v)
{
    // Initialize result
    size_t ret = v[0];

    for (int i = 1; i < v.size(); i++) {
        ret = (v[i] * ret) / gcd(v[i], ret);
    }

    return ret;
}

size_t PartTwo(Input input)
{
    vector<string> current_nodes;
    for (auto node_entry : input.nodes) {
        auto node = node_entry.first;
        if (node.back() == 'A') {
            current_nodes.push_back(node);
        }
    }

    vector<size_t> cycle_sizes;
    for (auto node : current_nodes) {
        auto [first_match, cycle_size] = FindPartTwoFirstMatchAndCycleSize(input, node);
        cycle_sizes.push_back(cycle_size);
    }

    return findlcm(cycle_sizes);
}
