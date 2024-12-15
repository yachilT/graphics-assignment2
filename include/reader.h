#pragma once
#include <Shapes.h>
#include <string>
#include <vector>
using std::vector;

using namespace std;

struct ReaderLine
{
    char c;
    float fs[4];
    
};


class Reader {
    private:
        vector<ReaderLine> lines;
        ReaderLine nextLine;
        void loadLines(const string &path);
        ReaderLine proccesLine(const string &l);
    public:
        Reader(const string &path);
        vector<ReaderLine> getLines() const;
        
};
