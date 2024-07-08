#include "linkedlist.h"
#include <string>
using namespace std;

class HashTable {
public:
    HashTable(int size);
    bool isEmpty();
    void insert(string key, double value);
    int search(string key);
    void remove(string key); // delete is a keyword
    void printTable();

private:
    int tableSize;
    int hash(std::string const& s);
    LinkedList* table;
};
