#include <cmath>
#include <string>
#include <iostream>
#include "markov_analyser.h"
#include "../util/file_reader.h"

using namespace std;

MarkovAnalyser::MarkovAnalyser(string filePath, string alphabetFilePath) {
    this->filePath = filePath;
    this->alphabetFilePath = alphabetFilePath;
    this->content = vector<string>();
    this->line = 0;
    this->content_size = 0;
}

void MarkovAnalyser::load() {
    FileReader fileReader = FileReader(filePath, alphabetFilePath);
    content = fileReader.readLines();
    this->content_size = content.size();
}

bool MarkovAnalyser::hasNextLine() {
    return line < content_size;
}

void MarkovAnalyser::incrementLine() {
    line++;
}

double MarkovAnalyser::getEstimatedBps(MarkovModel &model) {
    // fetch next line
    string txt = content[line];
    
    double estimatedBps = 0;
    string context = string(model.getMarkovModelOrder(), ' '); // initial context are white spaces
    for (char c: txt) {
        estimatedBps += -log2(model.getProbability(c, context));
        context = context.substr(1) + c;
    }
    return estimatedBps / (double) txt.size();
}