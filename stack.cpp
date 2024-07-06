#include "stack.h"
#include <iostream>

using namespace std;

Stack::Stack()
{
    capacity = 10;
    stack = new string[capacity];
    topIndex = -1;
}

Stack::Stack(int capacity)
{
    this->capacity = capacity;
    stack = new string[capacity];
    topIndex = -1;
}

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

    stack[++topIndex] = value;
}

void Stack::pop()
{
    if (topIndex == -1) {
        cout << "Stack is empty" << endl;
        return;
    }

    topIndex--;
}

string& Stack::top()
{
    if (topIndex == -1) {
        throw runtime_error("Stack is empty");
    }

    return stack[topIndex];
}

bool Stack::isEmpty()
{
    return topIndex == -1;
}

int Stack::size()
{
    return topIndex + 1;
}

void Stack::print()
{
    cout << "Stack: [ ";
    for (int i = 0; i <= topIndex; i++) {
        cout << stack[i] << " ";
    }
    cout << "]" << endl;
}
