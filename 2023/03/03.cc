#include "shared/shared.h"

#include <set>

using namespace std;

CharMatrix ReadInput(string file_path)
{
    auto lines = ReadLines(file_path);
    return CharMatrix(lines);
}

bool isSymbol(char c) { return c != '.' && !isdigit(c); }

int PartOne(CharMatrix &input)
{
    set<pair<int, int>> seen_points;
    vector<string> part_numbers;

    for (size_t y = 0; y < input.Height(); y++) {
        for (size_t x = 0; x < input.Width(); x++) {
            if (seen_points.find(make_pair(x, y)) != seen_points.end()) {
                continue;
            }
            seen_points.insert(make_pair(x, y));

            auto c = input.chars[y][x];
            if (!isdigit(c)) {
                continue;
            }
            string part_number = "";
            auto next_char_idx = x;
            bool is_part_number = false;

            do {
                part_number.push_back(input.chars[y][next_char_idx]);
                auto neighbors = input.Neighbors(next_char_idx, y);
                for (auto neighbor : neighbors) {
                    if (isSymbol(neighbor)) {
                        is_part_number = true;
                        break;
                    }
                }
                seen_points.insert(make_pair(next_char_idx, y));
                next_char_idx++;
            } while (next_char_idx < input.Width() && isdigit(input.chars[y][next_char_idx]));

            if (is_part_number) {
                part_numbers.push_back(part_number);
            }
        }
    }

    auto part_numbers_sum = 0;
    for (auto part_number : part_numbers) {
        part_numbers_sum += atoi(part_number.c_str());
    }

    return part_numbers_sum;
}

vector<string> AdjacentPartNumbers(CharMatrix &matrix, int x, int y)
{
    vector<string> part_numbers;
    auto neighbors = matrix.NeighborPoints(x, y);
    set<pair<int, int>> seen_points;
    for (auto neighbor : neighbors) {
        if (seen_points.find(neighbor) != seen_points.end()) {
            continue;
        }

        if (!isdigit(matrix.chars[neighbor.second][neighbor.first])) {
            continue;
        }

        int start_x = neighbor.first;
        while (start_x > 0) {
            if (isdigit(matrix.chars[neighbor.second][start_x - 1])) {
                start_x--;
            } else {
                break;
            }
        }

        auto next_char_idx = start_x;
        string part_number = "";
        do {
            if (seen_points.find(make_pair(next_char_idx, neighbor.second)) != seen_points.end()) {
                break;
            }
            part_number.push_back(matrix.chars[neighbor.second][next_char_idx]);
            seen_points.insert(make_pair(next_char_idx, neighbor.second));
            next_char_idx++;
            // This means we're parsing a number we've already seen
        } while (next_char_idx < matrix.Width()
            && isdigit(matrix.chars[neighbor.second][next_char_idx]));

        part_numbers.push_back(part_number);
    }

    return part_numbers;
}

int PartTwo(CharMatrix &input)
{
    vector<int> gear_ratios;
    for (size_t y = 0; y < input.Height(); y++) {
        for (size_t x = 0; x < input.Width(); x++) {
            auto c = input.chars[y][x];
            if (c != '*') {
                continue;
            }

            auto adjacent_part_numbers = AdjacentPartNumbers(input, x, y);
            if (adjacent_part_numbers.size() != 2) {
                continue;
            }

            auto first_gear_number = atoi(adjacent_part_numbers[0].c_str());
            auto second_gear_number = atoi(adjacent_part_numbers[1].c_str());
            auto gear_ratio = first_gear_number * second_gear_number;
            gear_ratios.push_back(gear_ratio);
        }
    }

    int gear_ratios_sum = 0;
    for (auto ratio : gear_ratios) {
        gear_ratios_sum += ratio;
    }

    return gear_ratios_sum;
}

int main(int argc, char const *argv[])
{
    auto input = ReadInput("inputs/03.txt");
    // auto input = ReadInput("inputs/03.test.txt");

    cout << "Part One: " << PartOne(input) << endl;
    cout << "Part Two: " << PartTwo(input) << endl;

    return 0;
}
