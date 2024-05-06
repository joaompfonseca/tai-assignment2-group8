#ifndef TAI_ASSIGNMENT2_GROUP8_PROGRAM_ARGUMENTS_H
#define TAI_ASSIGNMENT2_GROUP8_PROGRAM_ARGUMENTS_H

#include <iostream>

using namespace std;

struct ProgramArguments {
    string rhFilePath; // text not rewritten by ChatGPT
    string rcFilePath; // text rewritten by ChatGPT
    string tFilePath; // text under analysis
    unsigned int markovModelOrder{};
    double smoothingFactor{};
    unsigned int reduceFactor = 2;

    // overload the << operator to print the program arguments
    friend ostream &operator<<(ostream &os, const ProgramArguments &args) {
        os << "(-n) Text not rewritten by ChatGPT file path: " << args.rhFilePath << endl;
        os << "(-r) Text rewritten by ChatGPT file path: " << args.rcFilePath << endl;
        os << "(-t) Text under analysis file path: " << args.tFilePath << endl;
        os << "(-k) Markov model order: " << args.markovModelOrder << endl;
        os << "(-s) Smoothing factor: " << args.smoothingFactor << endl;
        os << "(-d) Reduce factor: " << args.reduceFactor;
        return os;
    }
};

ProgramArguments getProgramArguments(int argc, char *argv[]);

#endif //TAI_ASSIGNMENT2_GROUP8_PROGRAM_ARGUMENTS_H
