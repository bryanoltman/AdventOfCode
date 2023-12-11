#include <cstddef>
#include <iostream>
#include <set>

#include "10/10.h"
#include "shared/shared.h"

using namespace std;

static const char START = 'S';
static const char GROUND = '.';
static const array<char, 6> pipe_types = { 'J', 'L', '7', 'F', '|', '-' };

static const pair<int, int> UP = make_pair(0, -1);
static const pair<int, int> RIGHT = make_pair(1, 0);
static const pair<int, int> LEFT = make_pair(-1, 0);
static const pair<int, int> DOWN = make_pair(0, 1);

Input ParseInput(const string &filename)
{
    auto lines = ReadLines(filename);
    auto matrix = CharMatrix(lines);
    return matrix;
}

pair<size_t, size_t> FindStart(Input input)
{
    for (auto y = 0; y < input.Height(); y++) {
        for (auto x = 0; x < input.Width(); x++) {
            if (input.chars[y][x] == START) {
                return make_pair(x, y);
            }
        }
    }

    cerr << "Could not find start" << endl;
    exit(-1);
}

// You can enter pipe [c] if you are moving from the source char in one of the
// directions in the returned set.
set<pair<long, long>> EnterableDirections(char c)
{
    switch (c) {
    case GROUND:
        return {};
    case START:
        return { UP, DOWN, LEFT, RIGHT };
    case '|':
        return { UP, DOWN };
    case '-':
        return { LEFT, RIGHT };
    case 'F':
        return { LEFT, UP };
    case '7':
        return { RIGHT, UP };
    case 'J':
        return { RIGHT, DOWN };
    case 'L':
        return { LEFT, DOWN };
    default:
        cerr << "Unknown char: " << c << endl;
        exit(-1);
    }
}

set<pair<long, long>> ExitableDirections(char source)
{
    auto enterable_directions = EnterableDirections(source);
    set<pair<long, long>> ret;
    for (auto &direction : enterable_directions) {
        ret.insert(make_pair(-direction.first, -direction.second));
    }
    return ret;
}

bool CanMove(Input input, pair<size_t, size_t> source, pair<size_t, size_t> dest)
{
    auto direction = make_pair(dest.first - source.first, dest.second - source.second);
    auto source_char = input.CharAt(source);
    auto dest_char = input.CharAt(dest);
    auto possible_exits = ExitableDirections(source_char);
    if (possible_exits.find(direction) == possible_exits.end()) {
        return false;
    }

    auto possible_entrances = EnterableDirections(dest_char);
    if (possible_entrances.find(direction) == possible_entrances.end()) {
        return false;
    }

    return true;
}

set<pair<size_t, size_t>> GetLoop(Input input)
{
    auto start_point = FindStart(input);
    auto seen_points = set<pair<size_t, size_t>>();
    auto num_steps = 0;
    auto current_point = start_point;
    do {
        seen_points.insert(current_point);
        auto neighbor_points
            = input.NeighborPoints(current_point.first, current_point.second, false);
        for (auto &neighbor_point : neighbor_points) {
            if (!CanMove(input, current_point, neighbor_point)) {
                continue;
            }

            // If we've reached the start after moving more than one step away,
            // we've completed the loop.
            if (num_steps > 1 && input.CharAt(neighbor_point) == START) {
                num_steps++;
                return seen_points;
            }

            if (seen_points.find(neighbor_point) != seen_points.end()) {
                continue;
            }

            current_point = neighbor_point;
            num_steps++;
            break;
        }
    } while (input.CharAt(current_point) != START);

    return seen_points;
}

size_t PartOne(Input input)
{
    auto loop = GetLoop(input);
    return loop.size() / 2;
}

bool isInsideLoop(Input input, set<pair<size_t, size_t>> loop, pair<size_t, size_t> point)
{
    if (loop.find(point) != loop.end()) {
        return false;
    }

    bool is_on_horizontal_pipe = false;
    // Just a dummy value to start with
    auto horizontal_pipe_start_char = ' ';
    size_t num_crossings = 0;
    for (auto i = point.first + 1; i < input.Width(); i++) {
        auto current_point = make_pair(i, point.second);
        if (loop.find(current_point) != loop.end()) {
            auto c = input.CharAt(current_point);
            if (c == 'J' || c == 'L' || c == 'F' || c == '7') {
                if (is_on_horizontal_pipe) {
                    // We're going W->E, starting pipes can only be L or F (SE or NE)
                    if (horizontal_pipe_start_char == 'L' && c == '7') {
                        num_crossings++;
                    } else if (horizontal_pipe_start_char == 'F' && c == 'J') {
                        num_crossings++;
                    }
                    is_on_horizontal_pipe = false;
                } else {
                    horizontal_pipe_start_char = c;
                    is_on_horizontal_pipe = true;
                }
            } else if (c == '|') {
                num_crossings++;
            }
        }
    }

    return num_crossings % 2 == 1;
}

char StartingPointValue(Input input, pair<size_t, size_t> start, set<pair<size_t, size_t>> loop)
{
    vector<pair<size_t, size_t>> adjacent_loop_points;
    for (auto &neighbor_point : input.NeighborPoints(start.first, start.second, false)) {
        if (loop.find(neighbor_point) == loop.end()) {
            continue;
        }
        if (CanMove(input, start, neighbor_point)) {
            adjacent_loop_points.push_back(neighbor_point);
        }
    }

    if (adjacent_loop_points.size() != 2) {
        cerr << "Expected two adjacent loop chars, got " << adjacent_loop_points.size() << endl;
        exit(-1);
    }

    auto direction_a = make_pair(
        start.first - adjacent_loop_points[0].first, start.second - adjacent_loop_points[0].second);
    auto direction_b = make_pair(
        start.first - adjacent_loop_points[1].first, start.second - adjacent_loop_points[1].second);
    for (auto &pipe_type : pipe_types) {
        auto enterable_directions = EnterableDirections(pipe_type);
        if (enterable_directions.find(direction_a) != enterable_directions.end()
            && enterable_directions.find(direction_b) != enterable_directions.end()) {
            return pipe_type;
        }
    }

    cerr << "Could not find starting point value" << endl;
    exit(-1);
}

size_t PartTwo(Input input)
{
    auto start_point = FindStart(input);
    auto loop = GetLoop(input);
    auto starting_point_value = StartingPointValue(input, start_point, loop);
    input.chars[start_point.second][start_point.first] = starting_point_value;

    set<pair<size_t, size_t>> inside_loop_points;

    for (auto y = 0; y < input.Height(); y++) {
        for (auto x = 0; x < input.Width(); x++) {
            auto point = make_pair(x, y);
            if (isInsideLoop(input, loop, point)) {
                inside_loop_points.insert(point);
            }
        }
    }

    return inside_loop_points.size();
}
