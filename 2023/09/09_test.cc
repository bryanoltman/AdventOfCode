#include <catch2/catch.hpp>

#include "09/09.h"

using namespace std;

static auto TAGS = "Day 09";

TEST_CASE("Parses input", TAGS)
{
    auto input = ParseInput("inputs/09.test.txt");
    REQUIRE(input[0] == (vector<size_t>) { 0, 3, 6, 9, 12, 15 });
    REQUIRE(input[1] == (vector<size_t>) { 1, 3, 6, 10, 15, 21 });
    REQUIRE(input[2] == (vector<size_t>) { 10, 13, 16, 21, 30, 45 });
}

TEST_CASE("Derivatives", TAGS)
{
    vector<size_t> numbers = { 1, 3, 6, 10, 15, 21 };
    auto derivatives = Derivatives(numbers);
    REQUIRE(derivatives[0] == numbers);
    REQUIRE(derivatives[1] == (vector<size_t>) { 2, 3, 4, 5, 6 });
    REQUIRE(derivatives[2] == (vector<size_t>) { 1, 1, 1, 1 });
    REQUIRE(derivatives[3] == (vector<size_t>) { 0, 0, 0 });
}

TEST_CASE("NextNumberInSequence", TAGS)
{
    vector<size_t> numbers = { 1, 3, 6, 10, 15, 21 };
    REQUIRE(NextNumberInSequence(numbers) == 28);
}

TEST_CASE("Part 1", TAGS)
{
    auto input = ParseInput("inputs/09.test.txt");
    REQUIRE(PartOne(input) == 114);
}

// TEST_CASE("Part 2", TAGS)
// {
//     auto input = ParseInput("inputs/09.test.txt");
//     REQUIRE(PartTwo(input) == 0);
// }