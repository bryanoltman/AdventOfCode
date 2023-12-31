#include <catch2/catch.hpp>

#include "13/13.h"

using namespace std;

static auto TAGS = "Day 13";

TEST_CASE("ParseInput", TAGS)
{
    auto input = ParseInput("inputs/13.test.txt");
    REQUIRE(input.size() == 2);
}

TEST_CASE("VerticalReflectionIndex", TAGS)
{
    auto input = ParseInput("inputs/13.test.txt");
    REQUIRE(VerticalReflectionIndex(input[0], 0) == 5);
    REQUIRE(VerticalReflectionIndex(input[1], 0) == nullopt);
}

TEST_CASE("VerticalReflectionIndex (2)", TAGS)
{
    auto input = ParseInput("inputs/13.test2.txt");
    REQUIRE(VerticalReflectionIndex(input[0], 0) == 1);
}

TEST_CASE("HorizontalReflectionIndex", TAGS)
{
    auto input = ParseInput("inputs/13.test.txt");
    REQUIRE(HorizontalReflectionIndex(input[0], 0) == nullopt);
    REQUIRE(HorizontalReflectionIndex(input[1], 0) == 4);
}

TEST_CASE("HorizontalReflectionIndex (1 diff)", TAGS)
{
    auto input = ParseInput("inputs/13.test.txt");
    REQUIRE(HorizontalReflectionIndex(input[0], 1) == 3);
    REQUIRE(HorizontalReflectionIndex(input[1], 1) == 1);
}

TEST_CASE("VerticalReflectionIndex (1 diff)", TAGS)
{
    auto input = ParseInput("inputs/13.test.txt");
    REQUIRE(VerticalReflectionIndex(input[0], 1) == nullopt);
    REQUIRE(VerticalReflectionIndex(input[1], 1) == nullopt);
}

TEST_CASE("Part 1", TAGS)
{
    auto input = ParseInput("inputs/13.test.txt");
    REQUIRE(PartOne(input) == 405);
}

TEST_CASE("Part 2", TAGS)
{
    auto input = ParseInput("inputs/13.test.txt");
    REQUIRE(PartTwo(input) == 400);
}