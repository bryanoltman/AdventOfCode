#include <catch2/catch.hpp>

#include "11/11.h"

using namespace std;

static auto TAGS = "Day 11";

TEST_CASE("Part 1", TAGS)
{
    auto input = ParseInput("inputs/11.test.txt");
    REQUIRE(PartOne(input) == 4);
}

TEST_CASE("Part 2", TAGS)
{
    auto input = ParseInput("inputs/11.test.txt");
    REQUIRE(PartTwo(input) == 4);
}