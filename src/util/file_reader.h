#ifndef TAI_ASSIGNMENT2_GROUP8_FILE_READER_H
#define TAI_ASSIGNMENT2_GROUP8_FILE_READER_H

#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

class FileReader {
public:
    explicit FileReader(string filePath, unordered_set<char> alphabet = {});

    unordered_set<char> getAlphabet();

    vector<string> getLines();

    string getContent();

    void read();

private:
    string filePath;
    unordered_set<char> alphabet;
    vector<string> lines;
};

#endif //TAI_ASSIGNMENT2_GROUP8_FILE_READER_H