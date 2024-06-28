#include "hashtable.h"
#include <iostream>
#include <utility>

using namespace std;

HashTable::HashTable()
{
}

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

void HashTable::insert(char key, int value)
{
    int index = hash((char*)&key);
    auto& list = table[index];

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
        list.emplace_back(pair<char, int>(key, value));
    }

    return;
}

int HashTable::search(char key)
{
    int index = hash((char*)&key);
    auto& list = table[index];

    bool keyFound = false;
    for (auto pair = list.begin(); pair != list.end(); ++pair) {
        if (pair->first == key) {
            return pair->second;
        }
    }

    if (!keyFound) {
        cout << "[HashTable::search] Key not found" << endl;
    }
    return 0;
}

void HashTable::remove(char key)
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
unsigned long HashTable::hash(char* key)
{

    unsigned long hash = 5381;
    int c;
    while ((c = *key++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash % tableSize;
}
