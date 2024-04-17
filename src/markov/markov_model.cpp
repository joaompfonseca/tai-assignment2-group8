#include "markov_model.h"
#include "../util/file_reader.h"

using namespace std;

MarkovModel::MarkovModel(string filePath, unsigned int markovModelOrder, double smoothingFactor) {
    this->filePath = filePath;
    this->markovModelOrder = markovModelOrder;
    this->smoothingFactor = smoothingFactor;
    this->table = unordered_map<string, unordered_map<char, unsigned int>>();
}

unsigned int MarkovModel::getMarkovModelOrder() const {
    return markovModelOrder;
}

void MarkovModel::load() {
    FileReader fileReader = FileReader(filePath);
    fileReader.read();

    string content = fileReader.getContent();

    string context = string(markovModelOrder, ' '); // initial context are white spaces
    for (char c: content) {
        table[context][c]++;
        context = context.substr(1) + c;
    }
}

double MarkovModel::getProbability(char event, string context) {
    unsigned int count_e_given_c = table[context][event];
    unsigned int count_all_given_c = 0;
    for (auto& [e, count]: table[context]) {
        count_all_given_c += count;
    }
    return (count_e_given_c + smoothingFactor) / (count_all_given_c + smoothingFactor * markovModelOrder);
}
