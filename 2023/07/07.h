#ifndef _2023_07_07_H_
#define _2023_07_07_H_

#include <cstddef>
#include <vector>

using namespace std;

enum Card {
    joker = 1,
    two = 2,
    three = 3,
    four = 4,
    five = 5,
    six = 6,
    seven = 7,
    eight = 8,
    nine = 9,
    ten = 10,
    jack = 11,
    queen = 12,
    king = 13,
    ace = 14,
};

enum HandType {
    high_card,
    one_pair,
    two_pair,
    three_of_a_kind,
    full_house,
    four_of_a_kind,
    five_of_a_kind,
};

struct Hand {
    array<Card, 5> cards;
    HandType type;

    static HandType DetermineHandType(array<Card, 5> cards);
    static HandType DetermineHandTypeWithJokers(array<Card, 5> cards);
    bool beats(Hand const other) const;
    string ToString() const;
};

struct HandBid {
    Hand hand;
    size_t bid;

    static HandBid parse(const string &line, bool use_jokers);
};

typedef vector<HandBid> Input;

Input ParseInput(const string &filename, bool use_jokers);

size_t PartOne(Input input);
size_t PartTwo(Input input);

#endif // _2023_07_07_H_