// Standing issues:
// make list dynamic to talbe size
#include <list>
using namespace std;

class HashTable {
public:
    HashTable();
    bool is_empty();
    void insert(char key, int value);
    int search(char key);
    void remove(char key); // delete is a keyword
    void printTable();

private:
    int tableSize = 26;
    unsigned long hash(char* key);
    list<pair<char, int>> table[26];
};
