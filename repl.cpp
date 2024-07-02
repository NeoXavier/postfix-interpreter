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
    // Print symbol table
    if (expression == "printTable") {
        symbolTable.printTable();
        return;
    }
    // Tokenise expression
    for (char& c : expression) {

        string token = "";
        token += c;

        if (isalpha(c) || isdigit(c)) {
            postfixStack.push(token);
            continue;
        }

        if (c == ' ') {
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            arithmetic(c);
        } else if (c == '=') {
            assignment();
        } else {
            cout << "Invalid character: " << c << endl;
        }
    }
    while (!postfixStack.empty()) {
        cout << ' ' << postfixStack.top();
        postfixStack.pop();
    }
    cout << endl;

    // Loop through tokens
    // If token is a number, push to postfixStack
    // If token is an operator
}

bool REPL::str_is_number(string& str)
{
    for (char& c : str) {
        if (!isdigit(c)) {
            if (c == '.' || c == '-')
                continue;
            cout << "[REPL::str_is_number] Not a number: " << c << endl;
            return false;
        }
    }
    return true;
}

bool REPL::str_is_alpha(string& str)
{
    for (char& c : str) {
        if (!isalpha(c)) {
            cout << "[REPL::str_is_alpha] Not a letter: " << c << endl;
            return false;
        }
    }
    return true;
}

int REPL::top_to_int()
{
    string& postfixStackTop = postfixStack.top();
    if (postfixStackTop.empty())
        throw std::runtime_error("Empty stack");

    if (str_is_number(postfixStackTop)) {
        cout << "[REPL::top_to_int] Number: " << postfixStackTop << endl;
        return stoi(postfixStackTop);
    }

    if (str_is_alpha(postfixStackTop)) {
        return symbolTable.search(postfixStackTop);
    }

    return 0;
}

void REPL::arithmetic(char& op)
{
    // First operand
    int num1 = top_to_int();
    postfixStack.pop();

    // Second operand
    int num2 = top_to_int();
    postfixStack.pop();

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

    cout << "[REPL::arithmetic]" << num1 << "+" << num2 << "=" << result << endl;
    postfixStack.push(to_string(result));
}

void REPL::assignment()
{
    // TODO:order and type checking
    int num = stoi(postfixStack.top());
    postfixStack.pop();

    string var = postfixStack.top();
    postfixStack.pop();

    // Insert into hashtable
    symbolTable.insert(var, num);
}
