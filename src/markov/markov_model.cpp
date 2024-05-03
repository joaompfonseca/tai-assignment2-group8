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
    string cachePath = filePath + ".cache";

    if (!loadTableFromCache(cachePath)) {
        FileReader fileReader = FileReader(filePath);
        fileReader.read();

        string content = fileReader.getContent();

        string context = string(markovModelOrder, ' '); // initial context are white spaces
        for (char event: content) {
            table[context][event]++;
            context = context.substr(1) + event;
        }

        saveTableToCache(cachePath);
    }
}

void MarkovModel::saveTableToCache(const string &cachePath) {
    ofstream file(cachePath);
    for (auto &[context, eventCount]: table) {
        for (auto &[event, count]: eventCount) {
            file << context << " " << event << " " << count << endl;
        }
    }
}

bool MarkovModel::loadTableFromCache(const string &cachePath) {
    ifstream file(cachePath);
    if (!file.is_open()) {
        return false;
    }
    string context;
    char event;
    unsigned int count;
    while (file >> context >> event >> count) {
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
