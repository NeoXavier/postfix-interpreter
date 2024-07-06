#include "hashtable.h"
#include <iostream>

using namespace std;

HashTable::HashTable(int size)
    : tableSize(size)
{
    table = new LinkedList[size];
}

bool HashTable::is_empty()
{
    for (int i = 0; i < tableSize; i++) {
        if (!table[i].isEmpty())
            return false;
    }
    return true;
}

void HashTable::insert(string key, int value)
{
    int index = hash(key);
    auto& list = table[index];

    // Check if key already exists
    bool keyFound = false;
    Node* nodePtr = list.head;

    // Search for key in linked list, if found, replace value
    while (nodePtr != nullptr) {
        if (nodePtr->key == key) {
            nodePtr->value = value;
            cout << "[HashTable::insert] Key already exists, replacing" + key + " with stored value " << value << endl;
            keyFound = true;
            break;
        }
        nodePtr = nodePtr->next;
    }

    if (!keyFound) {
        list.insertNode(key, value);
    }

    return;
}

int HashTable::search(string key)
{
    int index = hash(key);
    auto& list = table[index];

    cout << "[HashTable::search] Searching " + key + " at index " << index << endl;

    Node* nodePtr = list.head;

    while (nodePtr != nullptr) {
        if (nodePtr->key == key) {
            return nodePtr->value;
        }
        nodePtr = nodePtr->next;
    }

    cout << "[HashTable::search] Key not found" << endl;
    return 0;
}

void HashTable::remove(string key)
{

    int index = hash(key);
    auto& list = table[index];

    list.deleteNode(key);
    return;
}

void HashTable::printTable()
{
    cout << "Printing table" << endl;
    cout << "--------------" << endl;
    for (int i = 0; i < tableSize; i++) {
        if (table[i].isEmpty())
            continue;
        cout << "List index: " << i << endl;
        table[i].printList();
    }
    cout << "--------------" << endl;
}
int HashTable::getIndex(string key)
{
    return hash(key);
}

// djb2 hash function from https://stackoverflow.com/questions/19892609/djb2-by-dan-bernstein-for-c
int HashTable::hash(std::string const& s)
{
    unsigned long hash = 5381;
    for (auto c : s) {
        hash = (hash << 5) + hash + c; /* hash * 33 + c */
    }
    return hash % tableSize;
}
