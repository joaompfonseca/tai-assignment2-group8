#ifndef TAI_ASSIGNMENT2_GROUP8_FILE_READER_H
#define TAI_ASSIGNMENT2_GROUP8_FILE_READER_H

#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

class FileReader {
public:
    FileReader(string filename);

    void read();

    string getContent();

    unordered_set<char> getAlphabet();

    vector<string> readLines();

private:
    string filePath;
    string content;
    unordered_set<char> alphabet;
};

#endif //TAI_ASSIGNMENT2_GROUP8_FILE_READER_H