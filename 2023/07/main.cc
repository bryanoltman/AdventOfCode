#include <iostream>

#include "07/07.h"

using namespace std;

int main(int argc, char const *argv[])
{
    Input partOneInput = ParseInput("inputs/07.txt", false);
    Input partTwoInput = ParseInput("inputs/07.txt", true);

    cout << "Part One: " << PartOne(partOneInput) << endl;
    cout << "Part Two: " << PartTwo(partTwoInput) << endl;

    return 0;
}
