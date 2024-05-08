#include <cmath>
#include <string>
#include "markov_analyser.h"
#include "../util/file_reader.h"

using namespace std;

MarkovAnalyser::MarkovAnalyser(string filePath, string alphabetFilePath) {
    this->filePath = filePath;
    this->alphabetFilePath = alphabetFilePath;
    this->lines = vector<string>();
    this->count = 0;
}

void MarkovAnalyser::load() {
    // load alphabet
    FileReader alphabetFileReader = FileReader(alphabetFilePath);
    alphabetFileReader.read();

    // load content to be analysed
    FileReader fileReader = FileReader(filePath, alphabetFileReader.getAlphabet());
    fileReader.read();

    lines = fileReader.getLines();
}

bool MarkovAnalyser::hasNextLine() {
    return count < lines.size();
}

void MarkovAnalyser::incrementLine() {
    count++;
}

double MarkovAnalyser::getEstimatedBps(MarkovModel &model) {
    // fetch next line
    string txt = lines[count];

    double estimatedBps = 0;
    string context = string(model.getMarkovModelOrder(), ' ');
    for (char c: txt) {
        estimatedBps += -log2(model.getProbability(c, context));
        context = context.substr(1) + c;
    }
    return estimatedBps / (double) (txt.size() - model.getMarkovModelOrder());
}