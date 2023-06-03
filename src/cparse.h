// AN ALTERNATIVE IMPLEMENTATION OF cparse WITHOUT OOP IMPLEMENTATION

#include <iostream>
#include <string>
#include <vector>
#include <map>


using namespace std;


typedef vector<vector<string>> array2d_t;


vector<string> build_argument(string arg_long,
  string arg_short, string default_value) {
    vector<string> arguments = {
        arg_long,
        arg_short,
        default_value
    };
    return arguments;
}


// PARSE COMMAND LINE ARGUMENTS BY COMPARING THEM TO EXPECTED, BUILT ARGUMENTS
map<string, string> parse_arguments(array2d_t blt, int argc, char **argv) {

    // DECLARE TABLE CONTAINING FOUND ARGUMENTS
    map<string, string> arguments;

    // ITERATE THROUGH PASSED ARGUMENTS
    for (int i = 0; i < argc; i++) {

        // ITERATE THROUGH BUILT ARGUMENTS
        for (int j = 0; j < blt.size(); j++) {

            // CHECK FOR:
            // LONG ARGUMENT FORM (--arg)
            // SHORT ARGUMENT FORM (-a)
            // i IN RANGE OF argv
            if ((argv[i] == string("--") + blt[j][0]) ||
               (argv[i] == string("-") + blt[j][1])) {

                // DECLARE HUMAN READABLE VARIABLES
                string key = blt[j][0];

                // CHECK THAT THE EXPECTED ARGUMENT HASN'T ALREADY BEEN
                // SATISFIED
                if (arguments[key] != "") {
                    cout << "Argument " << argv[i]
                         << " already satisfied\n";
                    continue;
                }

                // CHECK WHETHER VALUE HAS BEEN PROVIDED
                // ELSE SET TO DEFAULT
                string value;
                if (i + 1 < argc) {
                    value = argv[i + 1];
                } else {
                    value = blt[j][2];
                }

                arguments[key] = value;
            }
        }
    }
    return arguments;
}
