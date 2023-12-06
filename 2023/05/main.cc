#include <iostream>

#include "05/05.h"

using namespace std;

int main(int argc, char const *argv[])
{
    auto input = ParseInput("inputs/05.txt");
    // auto input = ParseInput("inputs/05.test.txt");

    cout << "Seeds: ";
    for (auto seed : input.seeds) {
        cout << seed << " ";
    }
    cout << endl;

    cout << "Maps:" << endl;
    for (auto &map : input.maps) {
        map.Print();
    }

    cout << "Part One: " << PartOne(input) << endl;
    // cout << "Part Two: " << PartTwo(input) << endl;

    return 0;
}
