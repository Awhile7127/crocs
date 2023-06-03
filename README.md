# crocs


## Description

A simple, command-line Rock, Paper, Scissors game with focus on
customisability.

Written in C++.


## Compiling

Simply run `make`.


## Usage

```
./crocs --config path_to_config
```

The program will then wait for your input, which must match any given
choice's name. For instance: `rock`, `paper`, `scissors` or `orange`.


### Adding custom moves

**Good news! I made this easier.**

Simply edit the `config.json` file where the program is located upon
execution and add custom entries.

Entries take the form of:

```
name: [ "beats", "beats" ]
```

... where `name` is the name of the move (e.g. rock, paper, scissors)
and each `beats` is the name of another move that this move beats.
For instance: `rock` beats `scissors`, so a typical `config.json` would
look like this:


```
{
    "rock" = [ "scissors" ],
    "paper" = [ "rock" ],
    "scissors" = [ "paper" ]
}
```
