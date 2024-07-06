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

////////////////////
// REPL FUNCTIONS //
///////////////////

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

////////////////
// OPERATIONS //
////////////////

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

    cout << "[REPL::arithmetic] " << num1 << op << num2 << "= " << result << endl;
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

//////////////////////
// Helper functions //
//////////////////////

// Checks if a string is a number
bool REPL::str_is_number(string& str)
{
    for (char& c : str) {
        if (!isdigit(c)) {
            if (c == '.' || c == '-')
                continue;
            return false;
        }
    }
    return true;
}

// Checks if a string is alphabetic
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

// Function to convert top of stack to integer
int REPL::top_to_int()
{
    // Get top of stack
    string& postfixStackTop = postfixStack->top();

    // If top of stack is a number, return it
    if (str_is_number(postfixStackTop)) {
        cout << "[REPL::top_to_int] Number: " << postfixStackTop << endl;
        return stoi(postfixStackTop);
    }

    // If top of stack is a variable, return its value
    if (str_is_alpha(postfixStackTop)) {
        return symbolTable->search(postfixStackTop);
    }

    return 0;
}
