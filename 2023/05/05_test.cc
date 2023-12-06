#include <catch2/catch.hpp>

#include "05/05.h"

using namespace std;

static auto TEST_TAG = "Day 5";

TEST_CASE("Maps source to dest", TEST_TAG)
{
    cout << "05/05_test.cc: Maps source to dest" << endl;
    auto input = ParseInput("inputs/05.test.txt");
    cout << "got input" << endl;
    auto first_map = input.maps[0];
    REQUIRE(first_map.DestValue(10) == 10);
    REQUIRE(first_map.DestValue(10) == 10);
    REQUIRE(first_map.DestValue(79) == 81);
    REQUIRE(first_map.DestValue(14) == 14);
    REQUIRE(first_map.DestValue(55) == 57);
    REQUIRE(first_map.DestValue(13) == 13);
}