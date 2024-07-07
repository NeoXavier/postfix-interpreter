#include "stack.h"
#include <iostream>

using namespace std;

// Default constructor
Stack::Stack()
{
    capacity = 10;
    stack = new string[capacity];
    topIndex = -1;
}

// Constructor if capacity is specified
Stack::Stack(int capacity)
{
    this->capacity = capacity;
    stack = new string[capacity];
    topIndex = -1;
}

// Adds an element to the top of the stack
void Stack::push(string value)
{
    // If the stack is full, double the capacity
    if (topIndex == capacity - 1) {
        string* newStack = new string[capacity * 2];
        for (int i = 0; i < capacity; i++) {
            newStack[i] = stack[i];
        }
        delete[] stack;
        stack = newStack;
        capacity *= 2;
    }

    // Increment topIndex and add value to stack
    stack[++topIndex] = value;
}

// "Removes" the top element of the stack
void Stack::pop()
{
    // If the stack is empty, print an error message
    if (topIndex == -1) {
        cout << "Stack is empty" << endl;
        return;
    }

    // Decrement topIndex
    topIndex--;
}

// Returns the top element of the stack
string& Stack::top()
{
    // If the stack is empty, throw an exception
    if (topIndex == -1) {
        throw runtime_error("Stack is empty");
    }

    return stack[topIndex];
}

// Returns true if the stack is empty
bool Stack::isEmpty()
{
    return topIndex == -1;
}

// Returns the number of elements in the stack
int Stack::size()
{
    return topIndex + 1;
}

// Prints the stack
void Stack::print()
{
    cout << "Stack: [ ";
    for (int i = 0; i <= topIndex; i++) {
        cout << stack[i] << " ";
    }
    cout << "]" << endl;
}
