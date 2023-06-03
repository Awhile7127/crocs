#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <json/json.h>
#include <fstream>

#include "cparse.h"
#include "classes.h"


using namespace std;


// READ CONFIG FILE AND RETURN POSSIBLE CHOICES
Json::Value read_config_file(string config) {

    // CHECK WHETHER THE CONFIG FILE EXISTS
    std::ifstream file(config, std::ifstream::binary);

    if (!file.is_open()) {
        cout << "No config.json file found\n";
        exit(1);
    }

    Json::Value root;
    file >> root;
    return root;
}



// CREATE "CHOICE" CLASSES
// FROM PASSED NAME AND VECTOR OF OTHER OBJECTS IT BEATS
Choice initialize_obj(string name, vector<string> beats) {
    Choice obj;
    obj.name = name;
    obj.beats = beats;
    return obj;
}


// GET PLAYER INPUT
string get_input(vector<Choice> choices) {
    cout << "Choose a move! Choices are:\n";

    for (int i = 0; i < choices.size(); i++) {
        cout << "> " << choices[i].name << "\n";
    }

    string inp;
    cin >> inp;

    // CHECK WHETHER THE PLAYER INPUT IS A VALID CHOICE
    for (int i = 0; i < choices.size(); i++) {
        if (choices[i].name == inp) {
            return inp;
        }
    }

    // IF IT ISN'T, EXIT THE PROGRAM
    exit(1);
}


bool play_move(vector<Choice> choices, string player_move) {

    // CHANGE RANDOM SEED - SO MOVES ARE RANDOMISED BETWEEN PROGRAM EXECUTIONS
    srand(time(nullptr));

    // PICK A RANDOM MOVE FROM THE CHOICES AVAILABLE
    int pos = rand() % choices.size();
    Choice move = choices[pos];

    cout << "Computer chose: " << move.name << "\n";

    // ITERATE THROUGH WHAT THE CHOSEN MOVE BEATS
    for (int i = 0; i < move.beats.size(); i++) {

        // IF THE PLAYER'S MOVE IS FOUND IN BEATABLE MOVES,
        // OR IF THE PLAYER'S MOVE IS THE SAME AS THE COMPUTER'S,
        // RETURN FALSE
        if ((move.beats[i] == player_move) || (move.name == player_move)) {
            return false;
        }
    }

    // OTHERWISE, THE PLAYER WON, SO RETURN TRUE
    return true;
}


int main(int argc, char **argv) {

    // FIND CONFIG FILE
    array2d_t arguments = {
        build_argument("config", "c", "")
    };

    map<string, string> returned = parse_arguments(arguments, argc, argv);

    // READ THE MOVES PLAYERS CAN MAKE
    Json::Value config = read_config_file(returned["config"]);

    // DECLARE A VECTOR FOR LATER USE
    // THIS IS THE VECTOR OF PLAYER MOVES
    vector<Choice> choices;

    // ITERATE OVER EACH JSON ARRAY ENTRY
    for (Json::Value::const_iterator itr = config.begin(); itr != config.end(); itr++) {

        // EXPLICITLY CONVERT FROM JSON::VALUE TO STRING
        string name = itr.key().asString();

        // INITALIZE A VECTOR OF OTHER MOVES THE CURRENTLY ITERATED ONE BEATS
        vector<string> beats;

        // ITERATE THROUGH ALL ELEMENTS IN THE CURRENTLY ITERATED ARRAY ENTRY
        for (int i = 0; i < config[name].size(); i++) {

            // EXPLICITLY CONVERT DATA TYPE FROM JSON::VALUE TO STRING
            // AND APPEND TO PREVIOUSLY DECLARED VECTOR
            string val = config[name][i].asString();
            beats.push_back(val);
        }

        // INITAILIZE OBJECT WITH CLASS STRUCTURE AND PUSH TO VECTOR OF CHOICES
        choices.push_back(initialize_obj(name, beats));
    }


    // GET PLAYER MOVE
    string player_move;
    player_move = get_input(choices);

    // GENERATE THE COMPUTER'S MOVE AND PLAY AGAINST THE PLAYER
    bool result;
    result = play_move(choices, player_move);

    // EVALUATE THE RESULT
    if (result) {
        cout << "You won!\n";
    } else {
        cout << "You lost!\n";
    }

    return 1;
}
