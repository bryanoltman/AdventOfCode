#ifndef INC_2023_01_01_H
#define INC_2023_01_01_H

#include <string>
#include <utility>
#include <vector>

using namespace std;

static const vector<pair<string, string>> LETTER_PAIRS = {
    make_pair("one", "1"),
    make_pair("two", "2"),
    make_pair("three", "3"),
    make_pair("four", "4"),
    make_pair("five", "5"),
    make_pair("six", "6"),
    make_pair("seven", "7"),
    make_pair("eight", "8"),
    make_pair("nine", "9"),
};

char FirstDigitChar(string str);

char LastDigitChar(string str);

uint32_t PartOne(vector<string> input);

void SwapLetters(string &line);

char first_digit(string str);

char last_digit(string str);

uint32_t PartTwo(vector<string> input);

#endif // INC_2023_01_01_H