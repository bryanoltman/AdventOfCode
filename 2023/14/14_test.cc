#include <catch2/catch.hpp>

#include "14/14.h"

using namespace std;

static auto TAGS = "Day 14";

TEST_CASE("Part 1", TAGS)
{
    auto input = ParseInput("inputs/14.test.txt");
    REQUIRE(PartOne(input) == 136);
}

TEST_CASE("Part 2", TAGS)
{
    auto input = ParseInput("inputs/14.test.txt");
    REQUIRE(PartTwo(input) == 64);
}