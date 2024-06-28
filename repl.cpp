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
    if (expression == "printTable") {
        symbolTable.printTable();
        return;
    }
    // Tokenise expression
    for (char& c : expression) {
        if (isalpha(c) || isdigit(c)) {
            postfixStack.push(c);
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

    // Loop through tokens
    // If token is a number, push to postfixStack
    // If token is an operator
}

void REPL::arithmetic(char& op)
{
    // First operand
    int num1;
    if (isalpha(postfixStack.top())) {
        num1 = symbolTable.search(postfixStack.top());
    } else {
        num1 = postfixStack.top();
        num1 += -'0';
    }
    postfixStack.pop();

    // Second operand
    int num2;
    if (isalpha(postfixStack.top()))
        num2 = symbolTable.search(postfixStack.top());
    else {
        num2 = postfixStack.top();
        num2 += -'0';
    }
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
    postfixStack.push(result);
}

void REPL::assignment()
{
    int num = postfixStack.top() - '0';
    postfixStack.pop();

    char var = postfixStack.top();
    postfixStack.pop();

    // Insert into hashtable
    symbolTable.insert(var, num);
}
