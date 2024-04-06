/*
#include <string>
#include <iostream>


void print_str(const char*,std::string,const int, const int);

int main()

{

    int lenght = 2;

    char str[] = {'A', 'B', 'C', 'D'};



    int n = sizeof str;

    print_str(str, "", n, lenght);  //Note: this function works on all cases and not just the case above

    return 0;

}

// The main recursive method to print all possible strings of length "length"
    void print_str(const char str[],std::string prefix,const int n, const int lenght)

    {

        if (lenght == 1)

            {

                for (int j = 0; j < n; j++)

                std::cout << prefix + str[j] << std::endl;

            }//Base case: lenght = 1, print the string "lenght" times + the remaining letter

        else

            {


               // One by one add all characters from "str" and recursively call for "lenght" equals to "lenght"-1
                for (int i = 0; i < n; i++)

                // Next character of input added
                print_str(str, prefix + str[i], n, lenght - 1);
                // "lenght" is decreased, because we have added a new character

            }

    }

*/

#include "MarkovModel.h"

using namespace std;

MarkovModel::MarkovModel(string stream, vector<char> alphabet, int lookbackSize, int missingThreshold, double smoothingFactor, int contextSize, int limit) {
    this->stream = stream;
    this->streamSize = stream.size();
    this->alphabet = alphabet;
    this->smoothingFactor = smoothingFactor;
    this->contextSize = contextSize;
    this->ptr = 0;

    // Overhead: 8 bits (alphabet size) + 8 bits per symbol
    this->estimatedNumberOfBits = 8.0 + alphabet.size() * 8.0;
}

void MarkovModel::initTable() {
    // generate all permutations (with repetition) of the alphabet of size contextSize with bitwise
    int n = alphabet.size();
    
    stack<pair<int, string>> s; // FILO data structure to simulate the recursive call stack
    s.push({contextSize, ""});

    while (!s.empty()) {
        pair<int, string> p = s.top();
        s.pop();

        if (p.first == 0) {
            cout << p.second << endl;
            for (char c : alphabet) {
                table[p.second][c] = 0;
            }
        } else {
            for (int i = 0; i < n; i++) {
                s.push({p.first - 1, p.second + alphabet[i]});
            }
        }

    }

}

bool MarkovModel::hasNext() {
    return ptr < streamSize;
}

void MarkovModel::runStep() {
    // Retrieve context and symbol
    context = ptr - contextSize < 0 ? string(contextSize - ptr, alphabet[0]) + stream.substr(0, ptr) : stream.substr(ptr - contextSize, contextSize);
    symbol = stream[ptr];

    // Probability estimation
    double sum = 0.0;
    for (char c : alphabet) {
        sum += table[context][c];
    }
    double prob = (table[context][symbol] + smoothingFactor) / (sum + smoothingFactor * alphabet.size());
    estimatedNumberOfBits += -log2(prob);

    // Update table
    table[context][symbol]++;
    ptr++;
}

int main() {
    string stream = "BABBAABABBB";
    vector<char> alphabet = {'A', 'B'};
    int lookbackSize = 2;
    int missingThreshold = 1;
    double smoothingFactor = 1.0;
    int contextSize = 2;
    int limit = 1;

    MarkovModel model(stream, alphabet, lookbackSize, missingThreshold, smoothingFactor, contextSize, limit);
    model.initTable();

    while (model.hasNext()) {
        model.runStep();
    }

    cout << model.estimatedNumberOfBits << endl;

    return 0;
}