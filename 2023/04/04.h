#include <set>
#include <string>

using namespace std;

class Card {
public:
    Card(string &str);
    int number;
    set<int> winning_numbers;
    set<int> drawn_numbers;
};