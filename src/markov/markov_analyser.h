#ifndef TAI_ASSIGNMENT2_GROUP8_MARKOV_ANALYSER_H
#define TAI_ASSIGNMENT2_GROUP8_MARKOV_ANALYSER_H

#include <iostream>
#include "markov_model.h"

using namespace std;

class MarkovAnalyser {
public:
    MarkovAnalyser(string filePath);

    void load();

    double getEstimatedBps(MarkovModel &model);

private:
    string filePath;
    string content;
};

#endif //TAI_ASSIGNMENT2_GROUP8_MARKOV_ANALYSER_H
