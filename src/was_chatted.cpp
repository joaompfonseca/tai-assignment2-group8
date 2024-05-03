#include <iostream>
#include "util/program_arguments.h"
#include "markov/markov_model.h"
#include "markov/markov_analyser.h"

using namespace std;

int main(int argc, char *argv[]) {
    // parse program arguments
    ProgramArguments args = getProgramArguments(argc, argv);

    // print program configuration
    cout << "Program configuration:" << endl
         << args << endl;

    // load model of text not rewritten by ChatGPT
    MarkovModel rhModel = MarkovModel(args.rhFilePath, args.markovModelOrder, args.smoothingFactor, args.reduceFactor);
    rhModel.load();

    // load model of text rewritten by ChatGPT
    MarkovModel rcModel = MarkovModel(args.rcFilePath, args.markovModelOrder, args.smoothingFactor, args.reduceFactor);
    rcModel.load();

    // load analyser of text under analysis
    MarkovAnalyser tAnalyser = MarkovAnalyser(args.tFilePath);
    tAnalyser.load();

    // estimate the bps of the text under analysis on both models
    double rhEstimatedBps = tAnalyser.getEstimatedBps(rhModel);
    double rcEstimatedBps = tAnalyser.getEstimatedBps(rcModel);

    cout << "Not rewritten by ChatGPT: " << rhEstimatedBps << " bps" << endl;
    cout << "Rewritten by ChatGPT: " << rcEstimatedBps << " bps" << endl;

    cout << "Result: text was probably " << ((rhEstimatedBps < rcEstimatedBps) ? "not " : "") << "rewritten by ChatGPT" << endl;

    return EXIT_SUCCESS;
}
