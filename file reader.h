#ifndef FILE_READER_H
#define FILE_READER_H

#include <sstream>
#include <string>
#include <fstream>
#include "evaluator.h"

using namespace std;

/*
 * Reads inputs from the input file and write output in the output file
 */
class FileReader {

private:

    // Gets the name and the volume and creates a tree node
    Evaluator evaluator;

public:

    /*
     * Splits the name and volume in the given string
     */
    void lineProcessor(const string &);

    /*
     * Gets inputs from the input file
     * Passes the output file to Evaluator and the Evaluator writes the results in it
     */
    void getInput();
};

void FileReader::lineProcessor(const string &line) {

    string name;
    int v = 0;

    stringstream ss(line);
    ss >> name;
    ss >> v;

    evaluator.getNodes(name, v);
}

void FileReader::getInput() {

    ifstream fin("input.txt");
    ofstream fout("output.txt");

    string line;
    getline(fin, line);
    int number = stoi(line);

    for (int i = 0; i < number; ++i) {
        getline(fin, line);
        lineProcessor(line);
    }

    while (fin.peek() != EOF) {

        getline(fin, line);
        string name1, name2;

        stringstream ss(line);
        ss >> name1;
        ss >> name2;

        evaluator.order(name1, name2);
    }

    evaluator.print(fout);

    fin.close();
    fout.close();
}

#endif
