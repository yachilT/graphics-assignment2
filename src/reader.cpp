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

ReaderLine Reader::proccesLine(const string &l)
{
    vector<string> tokens;
    istringstream stream(l);
    string tok;
    while (stream >> tok) {
        tokens.push_back(tok);
    }

    if (tokens.size() != 4) {
        cout << l + " has more or less than 4 values" << endl;
        throw exception();
    }
    ReaderLine r;
    
    if (tokens[0].size() != 1) {
        cout << tokens[0] + " isn't a single char";
        throw exception();
    }

    r.c = tokens[0][0];

    for (int i = 1; i < 4; i++) {
        try {
            r.fs[i] = stof(tokens[i]);
        }  catch (const std::invalid_argument& e) {
            cerr << "Error: Unable to convert string to float. Details: " << e.what() << endl;
            throw exception();
        }
    }

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
