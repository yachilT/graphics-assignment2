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
        /*
        parsed lines from txt
        */
        vector<ReaderLine> lines;
        /*
        Parse the txt file into a vector of Reader lines
        @param path path of the txt file
        */
        void loadLines(const string &path);
        /*
        convert a string to a ReaderLine, consists of one char and four floats
        */
        ReaderLine proccesLine(const string &l);
    public:
        Reader(const string &path);
        vector<ReaderLine> getLines() const;
        
};
