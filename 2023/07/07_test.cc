#include <catch2/catch.hpp>

#include "07/07.h"

using namespace std;

static auto TAGS = "Day 07";

// TEST_CASE("Parses hand bid", TAGS)
// {
//     HandBid hand_bid = HandBid::parse(string("32T3K 765"), false);
//     REQUIRE(hand_bid.bid == 765);
//     REQUIRE(hand_bid.hand.cards[0] == three);
//     REQUIRE(hand_bid.hand.cards[1] == two);
//     REQUIRE(hand_bid.hand.cards[2] == ten);
//     REQUIRE(hand_bid.hand.cards[3] == three);
//     REQUIRE(hand_bid.hand.cards[4] == king);
// }

// // TEST_CASE("Determines hand type", TAGS)
// // {
// //     REQUIRE(Hand { two, two, two, two, two }.type_without_jokers() == five_of_a_kind);
// //     REQUIRE(Hand { two, two, two, two, three }.type_without_jokers() == four_of_a_kind);
// //     REQUIRE(Hand { two, two, two, three, three }.type_without_jokers() == full_house);
// //     REQUIRE(Hand { two, two, two, three, four }.type_without_jokers() == three_of_a_kind);
// //     REQUIRE(Hand { two, two, three, three, four }.type_without_jokers() == two_pair);
// //     REQUIRE(Hand { two, two, three, four, five }.type_without_jokers() == one_pair);
// //     REQUIRE(Hand { two, three, four, five, six }.type_without_jokers() == high_card);
// // }

// TEST_CASE("Determines which hands beat other hands")
// {
//     auto five_of_a_kind_twos = Hand { two, two, two, two, two };
//     auto five_of_a_kind_aces = Hand { ace, ace, ace, ace, ace };
//     auto four_of_a_kind = Hand { two, two, two, two, three };
//     auto full_house = Hand { two, two, two, three, three };
//     REQUIRE(five_of_a_kind_aces.beats(five_of_a_kind_twos, false));
//     REQUIRE(five_of_a_kind_twos.beats(four_of_a_kind, false));
//     REQUIRE(four_of_a_kind.beats(full_house, false));
// }

// TEST_CASE("Hand comparison 1", TAGS)
// {
//     auto hand_a = Hand { eight, eight, eight, eight, five };
//     auto hand_b = Hand { eight, eight, eight, ace, eight };
//     REQUIRE(hand_b.beats(hand_a));
// }

// TEST_CASE("Hand comparison 2", TAGS)
// {
//     auto hand_bid_a = HandBid::parse("22777 170", false);
//     auto hand_bid_b = HandBid::parse("22927 170", false);
//     REQUIRE(hand_bid_a.hand.beats(hand_bid_b.hand, false));
// }

// TEST_CASE("Hand Bid Sorting", TAGS)
// {
//     vector<HandBid> bids = {
//         HandBid::parse("2K7AJ 170", false),
//         HandBid::parse("2KT4Q 190", false),
//         HandBid::parse("3K924 824", false),
//         HandBid::parse("2A6KQ 203", false),
//     };

//     sort(bids.begin(), bids.end());
//     REQUIRE(bids[0].bid == 170);
//     REQUIRE(bids[1].bid == 190);
//     REQUIRE(bids[2].bid == 203);
//     REQUIRE(bids[3].bid == 824);
// }

TEST_CASE("DetermineHandTypeWithJokers", TAGS)
{
    auto input = ParseInput("inputs/07.test.txt", true);

    REQUIRE(Hand::DetermineHandTypeWithJokers(input[0].hand.cards) == one_pair);
    REQUIRE(Hand::DetermineHandTypeWithJokers(input[0].hand.cards) == input[0].hand.type);
    REQUIRE(Hand::DetermineHandTypeWithJokers(input[1].hand.cards) == four_of_a_kind);
    REQUIRE(Hand::DetermineHandTypeWithJokers(input[1].hand.cards) == input[1].hand.type);
    REQUIRE(Hand::DetermineHandTypeWithJokers(input[2].hand.cards) == two_pair);
    REQUIRE(Hand::DetermineHandTypeWithJokers(input[2].hand.cards) == input[2].hand.type);
    REQUIRE(Hand::DetermineHandTypeWithJokers(input[3].hand.cards) == four_of_a_kind);
    REQUIRE(Hand::DetermineHandTypeWithJokers(input[3].hand.cards) == input[3].hand.type);
    REQUIRE(Hand::DetermineHandTypeWithJokers(input[4].hand.cards) == four_of_a_kind);
    REQUIRE(Hand::DetermineHandTypeWithJokers(input[4].hand.cards) == input[4].hand.type);
}

TEST_CASE("Part 1", TAGS)
{
    auto input = ParseInput("inputs/07.test.txt", false);
    REQUIRE(PartOne(input) == 6440);
}

TEST_CASE("Part 2", TAGS)
{
    auto input = ParseInput("inputs/07.test.txt", true);
    REQUIRE(PartTwo(input) == 5905);
}