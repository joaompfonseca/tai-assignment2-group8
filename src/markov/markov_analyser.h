#ifndef TAI_ASSIGNMENT2_GROUP8_MARKOV_ANALYSER_H
#define TAI_ASSIGNMENT2_GROUP8_MARKOV_ANALYSER_H

#include <iostream>
#include <vector>
#include "markov_model.h"

using namespace std;

class MarkovAnalyser {
public:
    MarkovAnalyser(string filePath);

    void load();

    double getEstimatedBps(MarkovModel &model);

    bool hasNextLine();

    void incrementLine();

private:
    string filePath;
    vector<string> content;
    int line;
    int content_size;
};

#endif //TAI_ASSIGNMENT2_GROUP8_MARKOV_ANALYSER_H
