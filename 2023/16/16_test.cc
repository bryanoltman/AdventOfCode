#include <catch2/catch.hpp>

#include "16/16.h"

using namespace std;

static auto TAGS = "Day 16";

TEST_CASE("ParseInput", TAGS) { auto input = ParseInput("inputs/16.test.txt"); }

TEST_CASE("Part 1", TAGS)
{
    auto input = ParseInput("inputs/16.test.txt");
    REQUIRE(PartOne(input) == 0);
}

TEST_CASE("Part 2", TAGS)
{
    auto input = ParseInput("inputs/16.test.txt");
    REQUIRE(PartTwo(input) == 0);
}