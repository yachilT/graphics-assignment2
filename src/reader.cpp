#include "reader.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>
#include <vector>

using std::vector;


Reader::Reader(const string &path) : lines()
{
    this->loadLines(path);
}

//TODO!: USE SSCANF
ReaderLine Reader::proccesLine(const string &l)
{
    ReaderLine r;
    sscanf(l.c_str(), "%c %f %f %f %f", &r.c, r.fs, r.fs + 1, r.fs + 2, r.fs + 3, r.fs + 4);
    return r;
}

void Reader::loadLines(const string &path)
{
    ifstream file(path);
    if (!file) {
        cerr << "Unable to open file.\n";
    }

    string line;
    while (getline(file, line)) {
        lines.push_back(proccesLine(line));
    }

    
}

vector<ReaderLine> Reader::getLines() const{
    return this->lines;
}
