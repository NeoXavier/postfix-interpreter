#include "stack.h"
#include <string>

#include "hashtable.h"

using namespace std;

class REPL {
public:
    REPL();

private:
    // REPL functions
    string prompt();
    void eval(string& expression);

    // Operations
    void arithmetic(string& op);
    void assignment();

    // Data members
    Stack* postfixStack;
    HashTable* symbolTable;

    // Helper functions
    bool str_is_number(string& str);
    bool str_is_alpha(string& str);
    int top_to_int();
};
