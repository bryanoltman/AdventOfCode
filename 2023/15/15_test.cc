#include <catch2/catch.hpp>

#include "15/15.h"

using namespace std;

static auto TAGS = "Day 15";

TEST_CASE("ParseInput", TAGS)
{
    auto input = ParseInput("inputs/15.test.txt");
    REQUIRE(input
        == (Input) {
            "rn=1",
            "cm-",
            "qp=3",
            "cm=2",
            "qp-",
            "pc=4",
            "ot=9",
            "ab=5",
            "pc-",
            "pc=6",
            "ot=7",
        });
}

TEST_CASE("Hash", TAGS)
{
    REQUIRE(Hash("HASH") == 52);
    REQUIRE(Hash("rn=1") == 30);
    REQUIRE(Hash("rn=1") == 30);
    REQUIRE(Hash("cm-") == 253);
    REQUIRE(Hash("qp=3") == 97);
    REQUIRE(Hash("cm=2") == 47);
    REQUIRE(Hash("qp-") == 14);
    REQUIRE(Hash("pc=4") == 180);
    REQUIRE(Hash("ot=9") == 9);
    REQUIRE(Hash("ab=5") == 197);
    REQUIRE(Hash("pc-") == 48);
    REQUIRE(Hash("pc=6") == 214);
    REQUIRE(Hash("ot=7") == 231);
}

TEST_CASE("Part 1", TAGS)
{
    auto input = ParseInput("inputs/15.test.txt");
    REQUIRE(PartOne(input) == 1320);
}

TEST_CASE("Part 2", TAGS)
{
    auto input = ParseInput("inputs/15.test.txt");
    REQUIRE(PartTwo(input) == 0);
}