#include "repl.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

REPL::REPL()
{
    postfixStack = new Stack(20);
    symbolTable = new HashTable(10);

    while (!exit) {
        string expression;
        expression = prompt();
        eval(expression);
    }
}

////////////////////
// REPL FUNCTIONS //
///////////////////

// Shows a prompt and gets the user input
string REPL::prompt()
{
    string input;
    cout << "> ";
    getline(cin, input);
    return input;
}

// Evaluates the expression
void REPL::eval(string& expression)
{
    // Print symbol table
    if (expression == "printTable") {
        symbolTable->printTable();
        return;
    }

    // Exit REPL
    if (expression == "exit") {
        exit = true;
        return;
    }

    // Clear stack
    if (expression == "clear") {
        postfixStack->clear();
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

        // If token is a math function
        else if (token == "sqrt" || token == "sin" || token == "cos" || token == "tan" || token == "log") {
            mathFunc(token);
        }

        // Token is an assignment operator
        else if (token == "=") {
            assignment();
        }

        // If token is a delete operator
        else if (token == "DEL") {
            del();
        }

        // If token is a search operator
        else if (token == "?") {
            search();
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

// Performs arithmetic operations using the top 2 elements of the stack based on the input operator
void REPL::arithmetic(string& op)
{
    // First operand
    double num1 = top_to_num();
    postfixStack->pop();

    // Second operand
    double num2 = top_to_num();
    postfixStack->pop();

    double result;
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

    cout << num1 << op << num2 << "= " << result << endl;
    postfixStack->push(to_string(result));
}

// Assigns a value to a variable using the top 2 elements of the stack
void REPL::assignment()
{
    // Get top two elements
    string el1 = postfixStack->top();
    postfixStack->pop();
    string el2 = postfixStack->top();
    postfixStack->pop();

    // Check if one is a number and the other is a variable
    if ((str_is_alpha(el1) && str_is_alpha(el2)) || (str_is_number(el1) && str_is_number(el2))) {
        throw std::invalid_argument("Invalid assignment");
        return;
    }

    double num;
    string var;

    // Determine which is the number and which is the variable
    if (str_is_number(el1)) {
        num = stod(el1);
        var = el2;
    } else {
        num = stod(el2);
        var = el1;
    }

    // Insert into hashtable
    symbolTable->insert(var, num);
}

void REPL::mathFunc(string& func)
{
    // Get top of stack
    double num = top_to_num();
    postfixStack->pop();
    // Perform math function
    double result;
    if (func == "sqrt") {
        result = sqrt(num);
    } else if (func == "sin") {
        result = sin(num);
    } else if (func == "cos") {
        result = cos(num);
    } else if (func == "tan") {
        result = tan(num);
    } else if (func == "log") {
        result = log(num);
    } else {
        throw std::invalid_argument("Invalid math function");
    }

    cout << func << "(" << num << ") = " << result << endl;
    postfixStack->push(to_string(result));
}

// Deletes a symbol from the symbol table
void REPL::del()
{
    // Get the key from top of the stack
    string& key = postfixStack->top();
    postfixStack->pop();

    // Check if key is a valid variable
    if (!str_is_alpha(key)) {
        throw std::invalid_argument("Invalid variable");
    }

    // Remove the key from the symbol table
    symbolTable->remove(key);
}

// Searches and prints the value of a variable in the symbol table
void REPL::search()
{
    // Get the key from top of the stack
    string& key = postfixStack->top();

    // Check if key is a valid variable
    if (!str_is_alpha(key)) {
        throw std::invalid_argument("Invalid variable");
    }

    // Search for the key in the symbol table
    double value = symbolTable->search(key);
    cout << key << " = " << value << endl;
    postfixStack->pop();
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
            return false;
        }
    }
    return true;
}

// Function to convert top of stack to a decimal number, as it can either be a number or a variable
double REPL::top_to_num()
{
    // Get top of stack
    string& postfixStackTop = postfixStack->top();

    // If top of stack is a number, return it
    if (str_is_number(postfixStackTop)) {
        return stod(postfixStackTop);
    }

    // If top of stack is a variable, return its value
    if (str_is_alpha(postfixStackTop)) {
        return symbolTable->search(postfixStackTop);
    }

    return 0;
}
