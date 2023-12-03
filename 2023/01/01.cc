#include <map>
#include <string>
#include <vector>

#include "shared/shared.h"

using namespace std;

char FirstDigitChar(string str)
{
    for (char &c : str) {
        if (isdigit(c)) {
            return c;
        }
    }

    cout << "No digit found in " << str << endl;
    exit(-1);
}

char LastDigitChar(string str)
{
    reverse(str.begin(), str.end());
    for (char &c : str) {
        if (isdigit(c)) {
            return c;
        }
    }

    cout << "No digit found in " << str << endl;
    exit(-1);
}

uint32_t PartOne(vector<string> input)
{
    uint32_t acc = 0;
    for (string &str : input) {
        auto first_digit = FirstDigitChar(str);
        auto last_digit = LastDigitChar(str);
        string digits_str("");
        digits_str.push_back(first_digit);
        digits_str.push_back(last_digit);
        auto number = stoi(digits_str);
        acc += number;
    }

    return acc;
}

vector<pair<string, string>> letter_pairs;

void SwapLetters(string &line)
{
    for (int i = 0; i < line.length(); i++) {
        for (auto &pair : letter_pairs) {
            auto word = pair.first;
            auto letter = pair.second;
            if (line.find(word) == i) {
                line.replace(line.find(word), word.length(), letter);
                continue;
            }
        }
    }
}

char first_digit(string str)
{
    SwapLetters(str);
    return FirstDigitChar(str);
}

char last_digit(string str)
{
    for (size_t i = str.length() - 1; i >= 0; i--) {
        // cout << str << " at " << i << " isdigit: " << isdigit(str[i]) << endl;
        if (isdigit(str[i])) {
            return str[i];
        }

        for (auto &pair : letter_pairs) {
            auto word = pair.first;
            auto letter = pair.second;
            // cout << str << " find " << word << " at " << i << endl;
            if (str.compare(i, word.length(), word) == 0) {
                return letter[0];
            }
        }
    }

    cout << "No digit found in " << str << endl;
    exit(-1);
}

uint32_t PartTwo(vector<string> input)
{
    uint32_t acc = 0;
    for (string &str : input) {
        string line(str);
        string digits_str("");
        digits_str.push_back(first_digit(str));
        digits_str.push_back(last_digit(str));
        auto number = stoi(digits_str);
        acc += number;
    }

    return acc;
}

int main(int argc, char const *argv[])
{
    letter_pairs.push_back({ "one", "1" });
    letter_pairs.push_back({ "two", "2" });
    letter_pairs.push_back({ "three", "3" });
    letter_pairs.push_back({ "four", "4" });
    letter_pairs.push_back({ "five", "5" });
    letter_pairs.push_back({ "six", "6" });
    letter_pairs.push_back({ "seven", "7" });
    letter_pairs.push_back({ "eight", "8" });
    letter_pairs.push_back({ "nine", "9" });

    // auto input = ReadLines("inputs/01.test2.txt");
    // PartTwo(input);

    auto input = ReadLines("inputs/01.txt");
    std::cout << "Part 1: " << PartOne(input) << "\n";
    std::cout << "Part 2: " << PartTwo(input) << "\n";
    return 0;
}
