// Standing issues:
// make list dynamic to talbe size
#include <list>
#include <string>
using namespace std;

class HashTable {
public:
    HashTable();
    bool is_empty();
    void insert(string key, int value);
    int search(string key);
    void remove(string key); // delete is a keyword
    void printTable();

private:
    int tableSize = 26;
    unsigned long hash(char* key) const;
    list<pair<string, int>> table[26];
    // unsigned long hash(char key) const;
};
