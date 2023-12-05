#include <string>
#include <vector>

using namespace std;

vector<string> ReadLines(string file_path);

vector<string> SplitString(const string &str, char delimiter);

string TrimString(const std::string &line);

class CharMatrix {
public:
    CharMatrix(vector<string> lines);
    vector<pair<int, int>> NeighborPoints(int x, int y, bool include_diagonal = true);
    vector<char> Neighbors(int x, int y, bool include_diagonal = true);
    vector<vector<char>> chars;

    size_t Height() { return chars.size(); }

    size_t Width()
    {
        if (chars.empty()) {
            return 0;
        }
        return chars[0].size();
    }

    void Print();
};
