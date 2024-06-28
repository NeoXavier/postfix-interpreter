#include <stack>
#include <string>
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
};
