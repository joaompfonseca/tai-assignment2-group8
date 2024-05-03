#include "program_arguments.h"

#include <unordered_set>
#include <getopt.h>

using namespace std;

ProgramArguments getProgramArguments(int argc, char *argv[]) {
    ProgramArguments args;
    unordered_set<char> requiredArgs;
    int opt;
    while ((opt = getopt(argc, argv, "n:r:t:k:s:h")) != -1) {
        switch (opt) {
            case 'n':
                args.rhFilePath = optarg;
                requiredArgs.insert('n');
                break;
            case 'r':
                args.rcFilePath = optarg;
                requiredArgs.insert('r');
                break;
            case 't':
                args.tFilePath = optarg;
                requiredArgs.insert('t');
                break;
            case 'k':
                try {
                    int arg = stoi(optarg);
                    if (arg <= 0) {
                        throw invalid_argument(nullptr);
                    }
                    args.markovModelOrder = arg;
                } catch (const invalid_argument &e) {
                    cerr << "Error: Markov model order (-k) must be an integer greater than 0." << endl;
                    exit(EXIT_FAILURE);
                }
                requiredArgs.insert('k');
                break;
            case 's':
                try {
                    double arg = stod(optarg);
                    if (arg < 0) {
                        throw invalid_argument(nullptr);
                    }
                    args.smoothingFactor = arg;
                } catch (const invalid_argument &e) {
                    cerr << "Error: Smoothing factor (-s) must be a double greater than or equal to 0." << endl;
                    exit(EXIT_FAILURE);
                }
                requiredArgs.insert('s');
                break;
            case 'd':
                try {
                    int arg = stoi(optarg);
                    if (arg <= 0) {
                        throw invalid_argument(nullptr);
                    }
                    args.reduceFactor = arg;
                } catch (const invalid_argument &e) {
                    cerr << "Error: Reduce factor (-d) must be an integer greater than 0." << endl;
                    exit(EXIT_FAILURE);
                }
                break;
            case 'h':
                cout << "Usage: ./was_chatted REQUIRED OPTIONAL" << endl
                     << "Required arguments:" << endl
                     << " -n rh_file_path       : path to the file containing the text not rewritten by ChatGPT (string)" << endl
                     << " -r rc_file_path       : path to the file containing the text rewritten by ChatGPT (string)" << endl
                     << " -t t_file_path        : path to the file containing the text under analysis (string)" << endl
                     << " -k markov_model_order : order of the Markov model (int)" << endl
                     << " -s smoothing_factor   : parameter to smooth the first probability estimation (double)" << endl
                     << "Optional arguments:" << endl
                     << " -h                    : shows how to use the program" << endl
                     << " -d reduce_factor      : factor to reduce the counts of the Markov model (int, default is 2)" << endl;
                exit(EXIT_SUCCESS);
            case '?':
                if (optopt == 'n' || optopt == 'r' || optopt == 't' || optopt == 'k' || optopt == 's' || optopt == 'd') {
                    cerr << "Option -" << static_cast<char>(optopt) << " requires an argument." << endl;
                } else {
                    cerr << "Unknown option -" << static_cast<char>(optopt) << endl;
                }
                exit(EXIT_FAILURE);
            default:
                exit(EXIT_FAILURE);
        }
    }
    // Ensure that required options are provided
    for (char requiredArg: {'n', 'r', 't', 'k', 's'}) {
        if (requiredArgs.find(requiredArg) == requiredArgs.end()) {
            cerr << "Error: Option -" << requiredArg << " is required." << endl;
            exit(EXIT_FAILURE);
        }
    }
    return args;
}