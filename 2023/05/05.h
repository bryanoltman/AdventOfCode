#include <cstddef>
#include <vector>

#include "shared/shared.h"

using namespace std;

struct Range {
    Range(size_t start, size_t end)
    {
        this->start = start;
        this->end = end;
        this->length = end - start;
    }

    size_t start;
    size_t end;
    size_t length;

    bool Contains(size_t value) const { return value >= start && value < end; }
};

struct SourceDestRanges {
    Range source_range;
    Range dest_range;
};

struct SourceDestMap {
    string source_name;
    string dest_name;
    vector<SourceDestRanges> ranges;

    void Print() const;
    size_t DestValue(size_t source) const;
};

struct Input {
    vector<size_t> seeds;
    vector<SourceDestMap> maps;
};

bool RangesOverlap(const Range &a, const Range &b);

Input ParseInput(const string &filename);

size_t PartOne(const Input &input);
size_t PartTwo(const Input &input);