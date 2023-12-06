#include <iostream>

#include "01/01.h"
#include "shared/shared.h"

using namespace std;

int main(int argc, char const *argv[])
{
    auto input = ReadLines("inputs/01.txt");

    cout << "Part One: " << PartOne(input) << endl;
    cout << "Part Two: " << PartTwo(input) << endl;

    return 0;
}
