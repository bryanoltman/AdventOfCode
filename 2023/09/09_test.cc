#include <catch2/catch.hpp>

#include "09/09.h"

using namespace std;

static auto TAGS = "Day 08";

TEST_CASE("Parses input", TAGS)
{
    auto input = ParseInput("inputs/09.test.txt");
    REQUIRE(input[0] == (vector<size_t>) { 0, 3, 6, 9, 12, 15 });
    REQUIRE(input[1] == (vector<size_t>) { 1, 3, 6, 10, 15, 21 });
    REQUIRE(input[2] == (vector<size_t>) { 10, 13, 16, 21, 30, 45 });
}

TEST_CASE("Part 1", TAGS)
{
    auto input = ParseInput("inputs/09.test.txt");
    REQUIRE(PartOne(input) == 0);
}

TEST_CASE("Part 2", TAGS)
{
    auto input = ParseInput("inputs/09.test.txt");
    REQUIRE(PartTwo(input) == 0);
}