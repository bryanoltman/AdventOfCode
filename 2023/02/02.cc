#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include "shared/shared.h"

using namespace std;

class CubeResult {
public:
    int number;
    string color;
};

class GameResult {
public:
    int game_number;
    vector<vector<CubeResult>> cubes;
};

vector<string> split_string(string str, char delimiter)
{

    vector<string> res;
    string s;
    stringstream ss(str);

    while (getline(ss, s, delimiter)) {
        res.push_back(s);
    }

    return res;
}

vector<GameResult> ParseInput(std::string file_path)
{
    auto line_regex = regex("^Game (\\d+): (.*)$");
    auto cube_regex = regex("(\\d+) (\\w+)");

    auto lines = ReadLines(file_path);
    vector<GameResult> results;
    for (string &line : lines) {
        smatch game_matches;
        regex_search(line, game_matches, line_regex);
        auto game_number = game_matches[1].str();

        auto cube_draws_str = game_matches[2].str();
        auto cube_draw_groups_strings = split_string(cube_draws_str, ';');
        vector<vector<CubeResult>> cube_draws;
        for (string &cube_draw_string : cube_draw_groups_strings) {
            vector<CubeResult> cubes;
            auto cube_draw_strings = split_string(cube_draw_string, ',');
            for (string &cube_draw : cube_draw_strings) {
                smatch cube_matches;
                regex_search(cube_draw, cube_matches, cube_regex);
                auto cube_number = cube_matches[1].str();
                auto cube_color = cube_matches[2].str();
                CubeResult cube = { stoi(cube_number), cube_color };
                cubes.push_back(cube);
            }

            cube_draws.push_back(cubes);
        }

        GameResult result = { stoi(game_number), cube_draws };
        results.push_back(result);
    }

    return results;
}

uint64_t PartOne(vector<GameResult> input)
{
    uint matching_games = 0;
    for (GameResult &result : input) {
        int min_red = 0;
        int min_green = 0;
        int min_blue = 0;
        for (vector<CubeResult> &cube_draw : result.cubes) {
            for (CubeResult &cube : cube_draw) {
                if (cube.color == "red") {
                    min_red = max(min_red, cube.number);
                } else if (cube.color == "green") {
                    min_green = max(min_green, cube.number);
                } else if (cube.color == "blue") {
                    min_blue = max(min_blue, cube.number);
                } else {
                    cout << "Unknown color: " << cube.color << endl;
                    exit(-1);
                }
            }
        }

        if (min_red <= 12 && min_green <= 13 && min_blue <= 14) {
            matching_games += result.game_number;
        }
    }

    return matching_games;
}

uint64_t PartTwo(vector<GameResult> input)
{
    auto game_score = 0;
    for (GameResult &result : input) {
        int min_red = 0;
        int min_green = 0;
        int min_blue = 0;
        for (vector<CubeResult> &cube_draw : result.cubes) {
            for (CubeResult &cube : cube_draw) {
                if (cube.color == "red") {
                    min_red = max(min_red, cube.number);
                } else if (cube.color == "green") {
                    min_green = max(min_green, cube.number);
                } else if (cube.color == "blue") {
                    min_blue = max(min_blue, cube.number);
                } else {
                    cout << "Unknown color: " << cube.color << endl;
                    exit(-1);
                }
            }
        }

        int power = min_red * min_blue * min_green;
        game_score += power;
    }

    return game_score;
}

int main(int argc, char const *argv[])
{
    // auto input = ParseInput("inputs/02.test.txt");
    auto input = ParseInput("inputs/02.txt");

    cout << "Part 1: " << PartOne(input) << endl;
    cout << "Part 2: " << PartTwo(input) << endl;

    return 0;
}
