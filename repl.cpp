#include "repl.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

REPL::REPL()
{
    postfixStack = new Stack(20);
    symbolTable = new HashTable(26);
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
        symbolTable->printTable();
        return;
    }

    istringstream iss(expression);
    string token;

    // Tokenize and loop through tokens
    while (getline(iss, token, ' ')) {

        // If token is an operator
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            arithmetic(token);
        }

        // Token is an assignment operator
        else if (token == "=") {
            assignment();
        }

        // If token is a number or alphabet, push to postfixStack
        else if (str_is_number(token) || str_is_alpha(token)) {
            postfixStack->push(token);
        }
        // Unknown token
        else {
            cout << "Invalid character: " << token << endl;
        }
    }
    postfixStack->print();
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
    string& postfixStackTop = postfixStack->top();
    if (str_is_number(postfixStackTop)) {
        cout << "[REPL::top_to_int] Number: " << postfixStackTop << endl;
        return stoi(postfixStackTop);
    }

    if (str_is_alpha(postfixStackTop)) {
        return symbolTable->search(postfixStackTop);
    }

    return 0;
}

void REPL::arithmetic(string& op)
{
    // First operand
    int num1 = top_to_int();
    postfixStack->pop();

    // Second operand
    int num2 = top_to_int();
    postfixStack->pop();

    int result;

    switch (op[0]) {
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
    postfixStack->push(to_string(result));
}

void REPL::assignment()
{
    // TODO:order and type checking
    int num = stoi(postfixStack->top());
    postfixStack->pop();

    string var = postfixStack->top();
    postfixStack->pop();

    // Insert into hashtable
    symbolTable->insert(var, num);
}
