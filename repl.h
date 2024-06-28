#include <stack>
#include <string>

#include "hashtable.h"

using namespace std;

class REPL {
public:
    REPL();

private:
    string prompt();
    void eval(string& expression);

    void arithmetic(char& op);
    void assignment();

    stack<char> postfixStack;
    HashTable symbolTable;
};
