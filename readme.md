# Postfix Interpreter

[![Video Title](https://img.youtube.com/vi/3qQ5HLUwAhU/0.jpg)](https://www.youtube.com/watch?v=3qQ5HLUwAhU)

## Description

REPL based CLI for interpreting postfix expressions.
Written in C++.

Features and commands:
- Symbol Table for storing variables (aka dictionary)
- Printing of symbol table
- Arithmetic calculations (+, -, \*, /)
- Support for floating point values
- Additional mathematical functions (sin, cos, tan, log, sqrt)
- Memory manipulation functions (Clearing of Postfix Stack)

## Getting Started

### Dependencies
Dependencies needed if you wish to compile the program from source.
* C++ Compiler (g++) C++11 or later

Alternatively, if you wish to use Nix and direnv, you can use the provided flake.nix file to install the dependencies.
Simply run `direnv allow` in the root directory of the project to activate the flake environment.

From there you can compile the program using the provided `g++ -std=c++11 *.cpp` command.

### Executing program

```
./a.out
```
or the name of the compiled binary if you have renamed it.


## Report
A [report](report.pdf) describing the various algorithms and data structures used in the program can be found in the root directory.

