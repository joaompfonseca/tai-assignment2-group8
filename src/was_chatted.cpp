#include <iostream>
#include "util/program_arguments.h"
#include "util/csv_logger.h"
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
    cout << "Loading models..." << endl;
    MarkovModel rhModel = MarkovModel(args.rhFilePath, args.alphabetFilePath, args.markovModelOrder, args.smoothingFactor, args.reduceFactor);
    rhModel.load();
    cout << "Loaded model with human-written text" << endl;

    // load model of text rewritten by ChatGPT
    MarkovModel rcModel = MarkovModel(args.rcFilePath, args.alphabetFilePath, args.markovModelOrder, args.smoothingFactor, args.reduceFactor);
    rcModel.load();
    cout << "Loaded model with ChatGPT-rewritten text" << endl;

    // load analyser of text under analysis
    MarkovAnalyser tAnalyser = MarkovAnalyser(args.tFilePath, args.alphabetFilePath);
    tAnalyser.load();

    CSVLogger logger;
    if (!args.logFilePath.empty()) {
       logger = CSVLogger(args.logFilePath);
    }

    cout << "Starting inference..." << endl;
    while (tAnalyser.hasNextLine()) {
        // estimate the bps of the text under analysis on both models
        double rhEstimatedBps = tAnalyser.getEstimatedBps(rhModel);
        double rcEstimatedBps = tAnalyser.getEstimatedBps(rcModel);

        if (args.logFilePath.empty()) {
            cout << "Not rewritten by ChatGPT: " << rhEstimatedBps << " bps" << endl;
            cout << "Rewritten by ChatGPT: " << rcEstimatedBps << " bps" << endl << endl;
            cout << "Result: text was probably " << ((rhEstimatedBps < rcEstimatedBps) ? "not " : "") << "rewritten by ChatGPT" << endl;
        }
        else {
            logger.append({to_string(rhEstimatedBps), to_string(rcEstimatedBps), ((rhEstimatedBps < rcEstimatedBps) ? "0" : "1")});
        }

        tAnalyser.incrementLine();
    }
    cout << "Job done." << endl;

    return EXIT_SUCCESS;
}
