#include "file_reader.h"
#include <fstream>
#include <iostream>

using namespace std;

FileReader::FileReader(string filePath, unordered_set<char> alphabet) {
    this->filePath = filePath;
    this->alphabet = alphabet;
    this->lines = vector<string>();
}

unordered_set<char> FileReader::getAlphabet() {
    return this->alphabet;
}

vector<string> FileReader::getLines() {
    return this->lines;
}

string FileReader::getContent() {
    string content;
    for (const string& line: lines) {
        content += line;
    }
    return content;
}

void FileReader::read() {
    bool createAlphabet = this->alphabet.empty();
    string rawLine, parsedLine;

    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filePath << endl;
        exit(EXIT_FAILURE);
    }
    while (getline(file, rawLine)) {
        parsedLine = "";
        for (char c: rawLine) {
            if (createAlphabet) {
                this->alphabet.insert(c);
            }
            else if (this->alphabet.find(c) == this->alphabet.end()) {
                continue;
            }
            parsedLine += c;
        }
        lines.push_back(parsedLine);
    }
}
