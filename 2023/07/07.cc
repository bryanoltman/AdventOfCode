#include <cstddef>
#include <iostream>
#include <set>

#include "07/07.h"
#include "shared/shared.h"

using namespace std;

char card_to_char(Card card)
{
    switch (card) {
    case two:
        return '2';
    case three:
        return '3';
    case four:
        return '4';
    case five:
        return '5';
    case six:
        return '6';
    case seven:
        return '7';
    case eight:
        return '8';
    case nine:
        return '9';
    case ten:
        return 'T';
    case jack:
    case joker:
        return 'J';
    case queen:
        return 'Q';
    case king:
        return 'K';
    case ace:
        return 'A';
    }
}

Card parse_card(char c, bool use_jokers)
{
    switch (c) {
    case '2':
        return two;
    case '3':
        return three;
    case '4':
        return four;
    case '5':
        return five;
    case '6':
        return six;
    case '7':
        return seven;
    case '8':
        return eight;
    case '9':
        return nine;
    case 'T':
        return ten;
    case 'J':
        return use_jokers ? joker : jack;
    case 'Q':
        return queen;
    case 'K':
        return king;
    case 'A':
        return ace;
    default:
        cout << "Unknown card: " << c << endl;
        exit(-1);
    }
}

// All cards that are not jokers (including jacks, which jokers have replaced)
static const set<Card> NonJokerCards
    = { two, three, four, five, six, seven, eight, nine, ten, queen, king, ace };

HandType Hand::DetermineHandTypeWithJokers(array<Card, 5> cards)
{
    vector<Card> non_jokers;
    for (auto card : cards) {
        if (card != joker) {
            non_jokers.push_back(card);
        }
    }

    if (non_jokers.size() == 5) {
        return Hand::DetermineHandType(cards);
    }

    // Jokers are wild, try every possible substitution for every joker
    vector<vector<Card>> hands_to_try = { non_jokers };
    while (hands_to_try[0].size() < 5) {
        vector<vector<Card>> new_hands_to_try;
        for (auto hand : hands_to_try) {
            for (auto card : NonJokerCards) {
                auto new_hand = hand;
                new_hand.push_back(card);
                new_hands_to_try.push_back(new_hand);
            }
        }
        hands_to_try = new_hands_to_try;
    }

    HandType best_hand_type = high_card;
    for (auto hand : hands_to_try) {
        for (auto card : hand) {
            cout << card_to_char(card);
        }
        cout << endl;

        array<Card, 5> hand_array;
        for (int i = 0; i < hand.size(); i++) {
            hand_array[i] = hand[i];
        }
        for (auto card : hand_array) {
            cout << card_to_char(card);
        }
        cout << endl;
        auto type = Hand::DetermineHandType(hand_array);
        if (type > best_hand_type) {
            best_hand_type = type;
        }
    }

    return best_hand_type;
}

HandType Hand::DetermineHandType(array<Card, 5> cards)
{
    auto sorted_cards = cards;
    sort(sorted_cards.begin(), sorted_cards.end());

    if (sorted_cards[0] == sorted_cards[4]) {
        return five_of_a_kind;
    } else if (sorted_cards[0] == sorted_cards[3]) {
        return four_of_a_kind;
    } else if (sorted_cards[1] == sorted_cards[4]) {
        return four_of_a_kind;
    } else if (sorted_cards[0] == sorted_cards[2] && sorted_cards[3] == sorted_cards[4]) {
        return full_house;
    } else if (sorted_cards[0] == sorted_cards[1] && sorted_cards[2] == sorted_cards[4]) {
        return full_house;
    } else if (sorted_cards[0] == sorted_cards[2]) {
        return three_of_a_kind;
    } else if (sorted_cards[1] == sorted_cards[3]) {
        return three_of_a_kind;
    } else if (sorted_cards[2] == sorted_cards[4]) {
        return three_of_a_kind;
    } else if (sorted_cards[0] == sorted_cards[1] && sorted_cards[2] == sorted_cards[3]) {
        return two_pair;
    } else if (sorted_cards[0] == sorted_cards[1] && sorted_cards[3] == sorted_cards[4]) {
        return two_pair;
    } else if (sorted_cards[1] == sorted_cards[2] && sorted_cards[3] == sorted_cards[4]) {
        return two_pair;
    } else if (sorted_cards[0] == sorted_cards[1]) {
        return one_pair;
    } else if (sorted_cards[1] == sorted_cards[2]) {
        return one_pair;
    } else if (sorted_cards[2] == sorted_cards[3]) {
        return one_pair;
    } else if (sorted_cards[3] == sorted_cards[4]) {
        return one_pair;
    }
    return high_card;
}

string Hand::ToString() const
{
    string ret;
    for (auto card : cards) {
        ret += card_to_char(card);
    }
    return ret;
}

bool Hand::beats(Hand const other) const
{
    if (this->type > other.type) {
        return true;
    } else if (this->type < other.type) {
        return false;
    }

    for (int i = 0; i < this->cards.size(); i++) {
        if (this->cards[i] > other.cards[i]) {
            return true;
        } else if (this->cards[i] < other.cards[i]) {
            return false;
        }
    }

    return false;
}

HandBid HandBid::parse(const string &line, bool use_jokers)
{
    HandBid bid;
    auto parts = SplitString(line, ' ');
    auto bid_str = parts[1];
    bid.bid = stoi(bid_str);

    auto hand_str = parts[0];
    for (int i = 0; i < hand_str.length(); i++) {
        bid.hand.cards[i] = parse_card(hand_str[i], use_jokers);
    }
    if (use_jokers) {
        bid.hand.type = Hand::DetermineHandTypeWithJokers(bid.hand.cards);
    } else {
        bid.hand.type = Hand::DetermineHandType(bid.hand.cards);
    }
    return bid;
}

Input ParseInput(const string &filename, bool use_jokers)
{
    auto lines = ReadLines(filename);

    Input ret;
    for (auto &line : lines) {
        ret.push_back(HandBid::parse(line, use_jokers));
    }

    return ret;
}

size_t compute_winnings(Input input)
{
    sort(input.begin(), input.end(), [](HandBid a, HandBid b) { return b.hand.beats(a.hand); });

    int winnings = 0;
    for (int i = 0; i < input.size(); i++) {
        auto hand_bid = input[i];
        winnings += hand_bid.bid * (i + 1);
    }

    return winnings;
}

size_t PartOne(Input input) { return compute_winnings(input); }

size_t PartTwo(Input input) { return compute_winnings(input); }
