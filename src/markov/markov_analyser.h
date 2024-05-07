#ifndef TAI_ASSIGNMENT2_GROUP8_MARKOV_ANALYSER_H
#define TAI_ASSIGNMENT2_GROUP8_MARKOV_ANALYSER_H

#include <iostream>
#include <vector>
#include "markov_model.h"

using namespace std;

class MarkovAnalyser {
public:
    MarkovAnalyser(string filePath, string alphabetFilePath);

    void load();

    double getEstimatedBps(MarkovModel &model);

    bool hasNextLine();

    void incrementLine();

private:
    string filePath;
    string alphabetFilePath;
    vector<string> content;
    unsigned int line;
    unsigned int content_size;
};

#endif //TAI_ASSIGNMENT2_GROUP8_MARKOV_ANALYSER_H
