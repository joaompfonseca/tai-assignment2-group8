#include <fstream>
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
    if (!loadTableFromCache()) {
        FileReader fileReader = FileReader(filePath);
        fileReader.read();

        string content = fileReader.getContent();

        string context = string(markovModelOrder, ' '); // initial context are white spaces
        for (char event: content) {
            table[context][event]++;
            context = context.substr(1) + event;
        }

        saveTableToCache();
    }
}

void MarkovModel::saveTableToCache() {
    string cachePath = filePath + ".order" + to_string(markovModelOrder) + ".cache";
    ofstream file(cachePath, ios::binary);
    for (auto &[context, events]: table) {
        for (auto &[event, count]: events) {
            file.write(context.c_str(), markovModelOrder);
            file.write(&event, 1);
            file.write(reinterpret_cast<const char *>(&count), sizeof(count));
        }
    }
}

bool MarkovModel::loadTableFromCache() {
    string cachePath = filePath + ".order" + to_string(markovModelOrder) + ".cache";
    ifstream file(cachePath);
    if (!file.is_open()) {
        return false;
    }
    string context;
    char event;
    unsigned int count;
    while (!file.eof()) {
        file.read(&context[0], markovModelOrder);
        file.read(&event, 1);
        file.read(reinterpret_cast<char *>(&count), sizeof(count));
        table[context][event] = count;
    }
    return true;
}

double MarkovModel::getProbability(char event, string context) {
    unsigned int count_e_given_c = table[context][event];
    unsigned int count_all_given_c = 0;
    for (auto &[e, count]: table[context]) {
        count_all_given_c += count;
    }
    return (count_e_given_c + smoothingFactor) / (count_all_given_c + smoothingFactor * markovModelOrder);
}
