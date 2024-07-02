#include "hashtable.h"
#include <iostream>
#include <utility>

using namespace std;

HashTable::HashTable() { }

bool HashTable::is_empty()
{
    int sum = 0;

    for (int i = 0; i < tableSize; i++) {
        sum += table[i].size();
    }

    if (sum == 0)
        return true;

    return false;
}

void HashTable::insert(string key, int value)
{
    int index = hash((char*)&key);
    auto& list = table[index];
    cout << "[HashTable::insert] Index: " << index << endl;

    // Check if key already exists
    bool keyFound = false;
    for (auto pair = list.begin(); pair != list.end(); ++pair) {
        if (pair->first == key) {
            pair->second = value;
            cout << "[HashTable::insert] Key already exists, replacing stored value" << endl;
            keyFound = true;
            break;
        }
    }

    if (!keyFound) {
        list.emplace_back(pair<string, int>(key, value));
    }

    return;
}

int HashTable::search(string key)
{
    cout << "[HashTable::search] [" << key << "]" << endl;
    int index = hash((char*)&key);
    cout << "[HashTable::search] Index: " << index << endl;
    auto& list = table[index];

    bool keyFound = false;
    for (auto pair = list.begin(); pair != list.end(); ++pair) {
        if (pair->first == key) {
            cout << "[HashTable::search] Key found" << endl;
            cout << "[HashTable::search] Value: " << pair->second << endl;
            return pair->second;
        }
    }

    if (!keyFound) {
        cout << "[HashTable::search] Key not found" << endl;
    }
    return 0;
}

void HashTable::remove(string key)
{

    int index = hash((char*)&key);
    auto& list = table[index];

    // Check if key already exists
    bool keyFound = false;
    for (auto pair = list.begin(); pair != list.end(); ++pair) {
        if (pair->first == key) {
            pair = list.erase(pair);
            keyFound = true;
            cout << "[HashTable::remove] Pair removed" << endl;
            break;
        }
    }

    if (!keyFound) {
        cout << "[HashTable::remove] Pair not found" << endl;
    }

    return;
}

void HashTable::printTable()
{
    cout << "Printing table" << endl;
    cout << "--------------" << endl;
    for (int i = 0; i < tableSize; i++) {
        if (table[i].size() == 0)
            continue;
        for (auto pair = table[i].begin(); pair != table[i].end(); ++pair) {
            cout << pair->first << " " << pair->second << " ";
        }
        cout << endl;
    }
    cout << "--------------" << endl;
}

// djb2 hash function from https://gist.github.com/MohamedTaha98/ccdf734f13299efb73ff0b12f7ce429f
unsigned long HashTable::hash(char* key) const
{

    unsigned long hash = 5381L;
    int c;
    while ((c = *key++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash % tableSize;
}

// Hash function for a single character (function overlaod)
/* unsigned long HashTable::hash(char key) const
{
    char keyStr[2] = { key, '\0' };
    return hash(keyStr);
} */
