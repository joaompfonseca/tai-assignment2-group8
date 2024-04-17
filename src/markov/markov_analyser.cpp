#include <cmath>
#include "markov_analyser.h"
#include "../util/file_reader.h"

using namespace std;

MarkovAnalyser::MarkovAnalyser(string filePath) {
    this->filePath = filePath;
    this->content = "";
}

void MarkovAnalyser::load() {
    FileReader fileReader = FileReader(filePath);
    fileReader.read();

    this->content = fileReader.getContent();
}

double MarkovAnalyser::getEstimatedBps(MarkovModel &model) {
    double estimatedBps = 0;
    string context = string(model.getMarkovModelOrder(), ' '); // initial context are white spaces
    for (char c: content) {
        estimatedBps += -log2(model.getProbability(c, context));
        context = context.substr(1) + c;
    }
    return estimatedBps / (double) content.size();
}