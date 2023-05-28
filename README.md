# crocs


## Description

A simple, command-line Rock, Paper, Scissors game with focus on
customisability.

Written in C++.


## Compiling

Simply run `make`.


## Usage

```
./crocs
```

The program will then wait for your input, which must match any given
choice's name. For instance: `rock`, `paper`, `scissors` or `orange`.


### Adding custom moves

Easily added by editing the `main.cpp` file:

Simply edit this section of code, following the same format:

```
Choice rock = initialize_obj("rock", vector<string>{"scissors"});
Choice paper = initialize_obj("paper", vector<string>{"rock"});
Choice scissors = initialize_obj("scissors", vector<string>{"paper"});

vector<Choice> choices = {rock, paper, scissors};
```

For instance, if I wanted to add `orange` as a move, where `orange` beats
paper, but is beaten by scissors and rock, I would edit the above to be:

```
Choice rock = initialize_obj("rock", vector<string>{"scissors", "orange"});
Choice paper = initialize_obj("paper", vector<string>{"rock"});
Choice scissors = initialize_obj("scissors", vector<string>{"paper", "orange"});
Choice orange = initialize_obj("orange", vector<string>{"paper"});

vector<Choice> choices = {rock, paper, scissors, orange};
```
