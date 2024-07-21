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

// Inserts a key-value pair into the hash table
/*
 * Pseudocode

 INSERT (key, value)
    index = HASH(key)
    list = table|index]
    nodePtr = list.head
    while nodePtr # NIL
        if nodePtr.key = key
            nodePtr.value = value
            return
        nodePtr = nodePtr.next
    Insert node (key, value) into list
    return

 */
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

// Searches for a key in the hash table and returns the value
/*
 * Pseudocode

 SEARCH (key)
    index = HASH(key)
    list = table[index]
    nodePtr = list.head
    while nodePtr # NIL
        if nodePtr.key = key
            return nodePtr.value
        nodePtr = nodePtr.next
    print "Key not found"
    return 0

 */
double HashTable::search(string key)
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

// Removes a key-value pair from the hash table
/*
 * Pseudocode

 DELETE (key)
    index = HASH(key)
    list = table[index]
    DELETE node with key from list
    return

 */
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
/*
 * Pseudocode

    hash = 5381
    for each character In s
        hash = hash × 33 + (ASCII value of character)
    return hash % tableSize

 */
int HashTable::hash(std::string const& s)
{
    unsigned long hash = 5381;
    for (auto c : s) {
        hash = (hash << 5) + hash + c; /* hash * 33 + c */
    }
    return hash % tableSize;
}
