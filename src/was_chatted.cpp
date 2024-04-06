#include <iostream>
#include <unistd.h>
#include <unordered_set>

using namespace std;

struct ProgramArguments {
    string rhFilePath; // text not rewritten by ChatGPT
    string rcFilePath; // text rewritten by ChatGPT
    string tFilePath; // text under analysis
    unsigned int markovModelOrder{};
    double smoothingFactor{};

    // overload the << operator to print the program arguments
    friend ostream &operator<<(ostream &os, const ProgramArguments &args) {
        os << "(-n) Text not rewritten by ChatGPT file path: " << args.rhFilePath << endl;
        os << "(-r) Text rewritten by ChatGPT file path: " << args.rcFilePath << endl;
        os << "(-t) Text under analysis file path: " << args.tFilePath << endl;
        os << "(-k) Markov model order: " << args.markovModelOrder << endl;
        os << "(-s) Smoothing factor: " << args.smoothingFactor << endl;
        return os;
    }
};

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
            case 'h':
                cout << "Usage: ./was_chatted REQUIRED OPTIONAL" << endl
                     << "Required arguments:" << endl
                     << " -n rh_file_path       : path to the file containing the text not rewritten by ChatGPT (string)" << endl
                     << " -r rc_file_path       : path to the file containing the text rewritten by ChatGPT (string)" << endl
                     << " -t t_file_path        : path to the file containing the text under analysis (string)" << endl
                     << " -k markov_model_order : order of the Markov model (int)" << endl
                     << " -s smoothing_factor   : parameter to smooth the first probability estimation (double)" << endl
                     << "Optional arguments:" << endl
                     << " -h                    : shows how to use the program" << endl;
                exit(EXIT_SUCCESS);
            case '?':
                if (optopt == 'n' || optopt == 'r' || optopt == 't' || optopt == 'k' || optopt == 's') {
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

int main(int argc, char *argv[]) {
    // parse program arguments
    ProgramArguments args = getProgramArguments(argc, argv);

    // print the program configuration
    cout << "Program configuration:" << endl
         << args << endl;

    return EXIT_SUCCESS;
}
