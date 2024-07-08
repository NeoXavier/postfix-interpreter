#include "hashtable.h"
#include <iostream>

using namespace std;

HashTable::HashTable(int size)
    : tableSize(size)
{
    table = new LinkedList[size];
}

bool HashTable::isEmpty()
{
    // Loop through all linked lists in the table
    for (int i = 0; i < tableSize; i++) {
        // Check that the linked list is empty, if not return false
        if (!table[i].isEmpty())
            return false;
    }
    return true;
}

void HashTable::insert(string key, double value)
{
    // Get the hash of the key and access the linked list at that index
    int index = hash(key);
    auto& list = table[index];

    Node* nodePtr = list.head;

    // Search for key in linked list, if found, replace value
    while (nodePtr != nullptr) {
        if (nodePtr->key == key) {
            nodePtr->value = value;
            cout << "Key already exists, replacing " + key + " with stored value " << value << endl;
            return;
        }
        nodePtr = nodePtr->next;
    }

    // If key does not exist in the list, insert it
    list.insertNode(key, value);

    return;
}

int HashTable::search(string key)
{
    // Get the hash of the key and access the linked list at that index
    int index = hash(key);
    auto& list = table[index];

    // Search for key in linked list, and return value if found
    Node* nodePtr = list.head;
    while (nodePtr != nullptr) {
        if (nodePtr->key == key) {
            return nodePtr->value;
        }
        nodePtr = nodePtr->next;
    }

    cout << "Key not found" << endl;
    return 0;
}

void HashTable::remove(string key)
{
    // Get the hash of the key and access the linked list at that index
    int index = hash(key);
    auto& list = table[index];

    // Delete node with key
    list.deleteNode(key);
    return;
}

// Prints table
void HashTable::printTable()
{
    cout << "Printing table" << endl;
    cout << "--------------" << endl;
    for (int i = 0; i < tableSize; i++) {
        if (table[i].isEmpty())
            continue;
        cout << "[ " << i << " ] ";
        table[i].printList();
    }
    cout << "--------------" << endl;
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
