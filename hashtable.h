// Standing issues:
// See if it is required to copy the key and values
#include "linkedlist.h"
#include <string>
using namespace std;

class HashTable {
public:
    HashTable(int size);
    bool is_empty();
    void insert(string key, int value);
    int search(string key);
    void remove(string key); // delete is a keyword
    void printTable();
    int getIndex(string key);

private:
    int tableSize;
    int hash(std::string const& s);
    LinkedList* table;
};
