#include <fstream>
#include <sstream>
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
    // load alphabet
    FileReader alphabetFileReader = FileReader(alphabetFilePath);
    alphabetFileReader.read();

    // generate hash of the alphabet file
    hash<string> hasher;
    size_t alphabetHash = hasher(alphabetFileReader.getContent());

    // convert the hash into a hex string
    stringstream ss;
    ss << hex << alphabetHash;
    string alphabetHashStr = ss.str();

    // set the alphabet size
    alphabetSize = alphabetFileReader.getAlphabet().size();

    // name of the cache file
    string cacheFilePath = filePath + "." + to_string(markovModelOrder) + "." +  alphabetHashStr + ".cache";

    // load table from cache or generate it
    if (!loadTableFromCache(cacheFilePath)) {
        FileReader fileReader = FileReader(filePath, alphabetFileReader.getAlphabet());
        fileReader.read();

        string content = fileReader.getContent();
        string context = content.substr(0, markovModelOrder);
        for (char event: content.substr(markovModelOrder)) {
            table[context][event]++;
            if (table[context][event] == UINT32_MAX) {
                reduceTable(); // reduce table to avoid overflow
            }
            context = context.substr(1) + event;
        }
        saveTableToCache(cacheFilePath);
    }
}

void MarkovModel::saveTableToCache(string cacheFilePath) {
    ofstream file(cacheFilePath, ios::binary);
    // save table
    for (auto &[context, events]: table) {
        for (auto &[event, count]: events) {
            file.write(context.c_str(), markovModelOrder);
            file.write(&event, 1);
            file.write(reinterpret_cast<const char *>(&count), sizeof(count));
        }
    }
}

bool MarkovModel::loadTableFromCache(string cacheFilePath) {
    ifstream file(cacheFilePath, ios::binary);
    if (!file.is_open()) {
        return false;
    }
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
    cout << "Loaded model from " << cacheFilePath << endl;
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
