#include <fstream>
#include <climits>
#include "markov_model.h"
#include "../util/file_reader.h"

using namespace std;

MarkovModel::MarkovModel(string filePath, string alphabetFilePath, unsigned int markovModelOrder, double smoothingFactor, unsigned int reduceFactor) {
    this->filePath = filePath;
    this->alphabetFilePath = alphabetFilePath;
    this->markovModelOrder = markovModelOrder;
    this->smoothingFactor = smoothingFactor;
    this->reduceFactor = reduceFactor;
    this->alphabetSize = 0;
    this->table = unordered_map<string, unordered_map<char, unsigned int>>();
}

unsigned int MarkovModel::getMarkovModelOrder() const {
    return markovModelOrder;
}

void MarkovModel::load() {
    if (!loadTableFromCache()) {
        FileReader fileReader = FileReader(filePath, alphabetFilePath);
        fileReader.read();

        alphabetSize = fileReader.getAlphabet().size();

        string content = fileReader.getContent();
        string context = content.substr(0, markovModelOrder);
        for (char event: content.substr(markovModelOrder)) {
            table[context][event]++;
            if (table[context][event] == UINT32_MAX) {
                reduceTable(); // reduce table to avoid overflow
            }
            context = context.substr(1) + event;
        }
        saveTableToCache();
    }
}

void MarkovModel::saveTableToCache() {
    string cachePath = filePath + ".order" + to_string(markovModelOrder) + ".cache";
    ofstream file(cachePath, ios::binary);
    // save alphabet size
    file.write(reinterpret_cast<const char *>(&alphabetSize), sizeof(alphabetSize));
    // save table
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
    ifstream file(cachePath, ios::binary);
    if (!file.is_open()) {
        return false;
    }
    // read alphabet size
    file.read(reinterpret_cast<char *>(&alphabetSize), sizeof(alphabetSize));
    // read table
    string context = string(markovModelOrder, ' ');
    char event;
    unsigned long count;
    while (!file.eof()) {
        file.read(&context[0], markovModelOrder);
        file.read(&event, 1);
        file.read(reinterpret_cast<char *>(&count), sizeof(count));
        table[context][event] = count;
    }
    cout << "Loaded model from " << cachePath << endl;
    return true;
}

void MarkovModel::reduceTable() {
    for (auto &[context, events]: table) {
        for (auto &[event, count]: events) {
            table[context][event] = count / reduceFactor;
        }
    }
}

double MarkovModel::getProbability(char event, string context) {
    unsigned int count_e_given_c = table[context][event];
    unsigned int count_all_given_c = 0;
    for (auto &[e, count]: table[context]) {
        if (count_all_given_c >= UINT32_MAX - count) {
            count_e_given_c /= reduceFactor;
            count_all_given_c /= reduceFactor;
        }
        count_all_given_c += count;
    }
    return ((double) count_e_given_c + smoothingFactor) / ((double) count_all_given_c + smoothingFactor * (double) alphabetSize);
}
