
#include <iostream>
#include <regex>

#include "04.h"
#include "shared/shared.h"

using namespace std;

static regex line_regex = regex("^Card\\s+(\\d+): ([\\d|\\s]+)\\|([\\d|\\s]+)$");

vector<int> LineToNumbers(const string &line)
{
    vector<int> numbers;
    auto numbers_str = SplitString(line, ' ');
    for (auto number_str : numbers_str) {
        auto trimmed = TrimString(number_str);
        if (trimmed.empty()) {
            continue;
        }
        numbers.push_back(atoi(trimmed.c_str()));
    }
    return numbers;
}

Card::Card(string &str)
{
    winning_numbers = set<int>();
    drawn_numbers = set<int>();

    smatch line_matches;
    regex_search(str, line_matches, line_regex);
    number = atoi(line_matches[1].str().c_str());
    auto winning_numbers_str = LineToNumbers(line_matches[2].str());
    winning_numbers = set<int>(winning_numbers_str.begin(), winning_numbers_str.end());
    auto drawn_numbers_str = LineToNumbers(line_matches[3].str());
    drawn_numbers = set<int>(drawn_numbers_str.begin(), drawn_numbers_str.end());
}

vector<Card> ParseInput(string file_path)
{
    auto lines = ReadLines(file_path);
    vector<Card> cards;
    for (string &line : lines) {
        Card card = Card(line);
        cards.push_back(card);
    }
    return cards;
}

int PartOne(vector<Card> cards)
{
    int score = 0;
    for (auto &card : cards) {
        int num_winning_numbers = 0;
        for (int number : card.drawn_numbers) {
            if (card.winning_numbers.find(number) != card.winning_numbers.end()) {
                num_winning_numbers++;
            }
        }

        // cout << "Card " << card.number << " has " << num_winning_numbers << " winning numbers"
        //      << endl;
        if (num_winning_numbers > 0) {
            // cout << "score is " << (1 << (num_winning_numbers - 1)) << endl;
            score += 1 << (num_winning_numbers - 1);
        }
    }
    return score;
}

int main(int argc, char const *argv[])
{
    // auto input = ParseInput("inputs/04.txt");
    auto input = ParseInput("inputs/04.test.txt");

    cout << "Part One: " << PartOne(input) << endl;
    // cout << "Part Two: " << PartTwo(input) << endl;

    return 0;
}
