#include "repl.h"
#include <iostream>
#include <stdexcept>
#include <string>

REPL::REPL()
{
    bool exit = false;
    while (!exit) {
        string expression;
        expression = prompt();
        eval(expression);
    }
}

string REPL::prompt()
{
    string input;
    cout << "> ";
    getline(cin, input);
    return input;
}

void REPL::eval(string& expression)
{
    // Tokenise expression
    for (char& c : expression) {
        if (isalpha(c) || isdigit(c)) {
            numStack.push(int(c - '0'));
            continue;
        }
        if (c == ' ') {
            cout << "Space" << endl;
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            arithmetic(c);
        } else if (c == '=') {
            cout << "Equal" << endl;
        } else {
            cout << "Invalid character: " << c << endl;
        }
    }
    while (!numStack.empty()) {
        cout << ' ' << numStack.top();
        numStack.pop();
    }
    cout << endl;

    // Loop through tokens
    // If token is a number, push to numStack
    // If token is an operator
}

void REPL::arithmetic(char& op)
{
    int num1 = numStack.top();
    numStack.pop();
    int num2 = numStack.top();
    numStack.pop();

    int result;

    switch (op) {
    case '+':
        result = num1 + num2;
        break;
    case '-':
        result = num1 - num2;
        break;
    case '*':
        result = num1 * num2;
        break;
    case '/':
        if (num2 == '0') {
            throw std::runtime_error("Division by zero");
        }
        result = num1 / num2;
        break;
    default:
        throw std::invalid_argument("Invalid operator");
    }

    numStack.push(result);
}
