#include <iostream>

#include "11/11.h"

using namespace std;

int main(int argc, char const *argv[])
{
    Input input = ParseInput("inputs/11.txt");

    cout << "Part One: " << PartOne(input) << endl;
    cout << "Part Two: " << PartTwo(input) << endl;

    return 0;
}
