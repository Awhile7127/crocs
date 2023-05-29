#include <iostream>
#include <string>
#include <vector>

#include "classes.h"


using namespace std;


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


int main() {

    // INITIALIZE INDIVIDUAL MOVE CHOICES
    Choice rock = initialize_obj("rock", vector<string>{"scissors"});
    Choice paper = initialize_obj("paper", vector<string>{"rock"});
    Choice scissors = initialize_obj("scissors", vector<string>{"paper"});

    // CREATE A VECTOR OF CHOICES TO ITERATE THROUGH LATER
    vector<Choice> choices = {rock, paper, scissors};

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
