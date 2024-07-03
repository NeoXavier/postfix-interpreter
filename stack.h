#include <string>

using namespace std;

class Stack {
public:
    Stack();
    Stack(int capacity);
    void push(string value);
    void pop();
    string& top();
    bool isEmpty();
    int size();
    void print();

private:
    string* stack;
    int capacity;
    int topIndex;
};
