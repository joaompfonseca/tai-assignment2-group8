#include "file_reader.h"
#include <fstream>
#include <iostream>

using namespace std;

FileReader::FileReader(string filePath, string alphabetFilePath) {
    this->filePath = filePath;
    this->alphabetFilePath = alphabetFilePath;
    this->content = "";
    this->alphabet = {};
}

void FileReader::read() {
    char c;

    ifstream alphabetFile(alphabetFilePath);
    if (!alphabetFile.is_open()) {
        cerr << "Unable to open file: " << alphabetFilePath << endl;
        exit(EXIT_FAILURE);
    }
    while (alphabetFile.get(c)) {
        c = tolower(c);
        this->alphabet.insert(c);
    }
    alphabetFile.close();

    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filePath << endl;
        exit(EXIT_FAILURE);
    }
    while (file.get(c)) {
        c = tolower(c);
        if (this->alphabet.find(c) == this->alphabet.end()) {
            continue;
        }
        this->content += c;
    }
    file.close();
}

vector<string> FileReader::readLines() {
    vector<string> lines;
    string line, normalizedLine;
    char c;

    ifstream alphabetFile(alphabetFilePath);
    if (!alphabetFile.is_open()) {
        cerr << "Unable to open file: " << alphabetFilePath << endl;
        exit(EXIT_FAILURE);
    }
    while (alphabetFile.get(c)) {
        c = tolower(c);
        this->alphabet.insert(c);
    }
    alphabetFile.close();

    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filePath << endl;
        exit(EXIT_FAILURE);
    }
    while (getline(file, line)) {
        normalizedLine = "";
        for (char cl: line) {
            cl = tolower(cl);
            if (this->alphabet.find(cl) == this->alphabet.end()) {
                continue;
            }
            normalizedLine += cl;
        }
        lines.push_back(normalizedLine);
    }
    file.close();

    return lines;
}

string FileReader::getContent() {
    return this->content;
}

unordered_set<char> FileReader::getAlphabet() {
    return this->alphabet;
}