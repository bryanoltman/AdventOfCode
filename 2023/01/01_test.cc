#include <catch2/catch.hpp>

#include "01/01.h"
#include "shared/shared.h"

using namespace std;

static auto TAGS = "Day 01";

TEST_CASE("Parses lines from input", TAGS)
{
    auto input = ReadLines("inputs/01.test.txt");
    vector<string> expected = {
        "1abc2",
        "pqr3stu8vwx",
        "a1b2c3d4e5f",
        "treb7uchet",
    };
    REQUIRE(input == expected);
}

TEST_CASE("FirstDigitChar", TAGS)
{
    REQUIRE(FirstDigitChar("1abc2") == '1');
    REQUIRE(FirstDigitChar("pqr3stu8vwx") == '3');
    REQUIRE(FirstDigitChar("a1b2c3d4e5f") == '1');
    REQUIRE(FirstDigitChar("treb7uchet") == '7');
}

TEST_CASE("Part 1", TAGS)
{
    auto input = ReadLines("inputs/01.test.txt");
    REQUIRE(PartOne(input) == 142);
}

TEST_CASE("Part 2", TAGS)
{
    auto input = ReadLines("inputs/01.test2.txt");
    REQUIRE(PartTwo(input) == 281);
}