#include <catch2/catch.hpp>

#include "10/10.h"

using namespace std;

static auto TAGS = "Day 10";

TEST_CASE("Part 1 (test input 1)", TAGS)
{
    auto input = ParseInput("inputs/10.test.txt");
    REQUIRE(PartOne(input) == 4);
}

TEST_CASE("Part 1 (test input 2)", TAGS)
{
    auto input = ParseInput("inputs/10.test2.txt");
    REQUIRE(PartOne(input) == 8);
}

TEST_CASE("Part 2 (small test input)", TAGS)
{
    auto input = ParseInput("inputs/10.test3.txt");
    REQUIRE(PartTwo(input) == 4);
}

TEST_CASE("Part 2 (medium test input)", TAGS)
{
    auto input = ParseInput("inputs/10.test4.txt");
    REQUIRE(PartTwo(input) == 8);
}

TEST_CASE("Part 2 (large test input)", TAGS)
{
    auto input = ParseInput("inputs/10.test5.txt");
    REQUIRE(PartTwo(input) == 10);
}