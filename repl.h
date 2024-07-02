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

    stack<string> postfixStack;
    HashTable symbolTable;

    bool str_is_number(string& str);
    bool str_is_alpha(string& str);
    int top_to_int();
};
