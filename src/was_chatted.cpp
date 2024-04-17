#include <iostream>
#include "util/program_arguments.h"

using namespace std;

int main(int argc, char *argv[]) {
    // parse program arguments
    ProgramArguments args = getProgramArguments(argc, argv);

    // print the program configuration
    cout << "Program configuration:" << endl
         << args << endl;

    return EXIT_SUCCESS;
}
