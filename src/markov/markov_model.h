#ifndef TAI_ASSIGNMENT2_GROUP8_MARKOV_MODEL_H
#define TAI_ASSIGNMENT2_GROUP8_MARKOV_MODEL_H

#include <iostream>
#include <unordered_map>

using namespace std;

class MarkovModel {
public:
    MarkovModel(string filePath, string alphabetFilePath, unsigned int markovModelOrder, double smoothingFactor, unsigned int reduceFactor);

    unsigned int getMarkovModelOrder() const;

    void load();

    double getProbability(char symbol, string context);

private:
    string filePath;
    string alphabetFilePath;
    unsigned int markovModelOrder;
    double smoothingFactor;
    unsigned int reduceFactor;
    unsigned int alphabetSize;
    unordered_map<string, unordered_map<char, unsigned int>> table;

    void saveTableToCache(string cacheFilePath);

    bool loadTableFromCache(string cacheFilePath);

    void reduceTable();
};

#endif //TAI_ASSIGNMENT2_GROUP8_MARKOV_MODEL_H
