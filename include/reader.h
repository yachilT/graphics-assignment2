#pragma once
#include <Shapes.h>
#include <string>
using namespace std;

struct ReaderLine
{
    char c;
    float fs[3];
    
};


class Reader {
    private:
        vector<ReaderLine> lines;
        void loadLines(const string &path);
        ReaderLine proccesLine(const string &l);
    public:
        Reader(const string &path);
};
