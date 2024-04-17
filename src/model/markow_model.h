#ifndef TAI_ASSIGNMENT2_GROUP8_SRC_COPYMODELRUNNER_H
#define TAI_ASSIGNMENT2_GROUP8_SRC_COPYMODELRUNNER_H

#include <string>
#include <map>
#include <unordered_map> 
#include <vector>
#include <iostream>
#include <cmath>
#include <memory>
#include <stack>

using namespace std;

class MarkovModel {
public:
    MarkovModel(string stream, vector<char> alphabet , int loopbackSize, int missingThreshold, double smoothingFactor, int contextSize, int limit = 1);
    bool hasNext();
    void runStep();
    void initTable();
    double estimatedNumberOfBits;

// TODO: remove not used methods and variables
private:
    string stream;
    int streamSize;
    double smoothingFactor;
    int contextSize;
    unordered_map<string, unordered_map<char, int>> table;
    int ptr;
    string context;
    char symbol;
    vector<char> alphabet;
};


#endif //TAI_ASSIGNMENT2_GROUP8_SRC_COPYMODELRUNNER_H
