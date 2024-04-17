#include "file_reader.h"
#include <fstream>
#include <iostream>

using namespace std;

FileReader::FileReader(string filePath) {
    this->filePath = filePath;
    this->content = "";
    this->alphabet = {};
}

void FileReader::read() {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filePath << endl;
        exit(EXIT_FAILURE);
    }
    char c;
    while (file.get(c)) {
        this->content += c;
        this->alphabet.insert(c);
    }
}

string FileReader::getContent() {
    return this->content;
}

unordered_set<char> FileReader::getAlphabet() {
    return this->alphabet;
}