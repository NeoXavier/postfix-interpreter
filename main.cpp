// #include "repl.h"

#include "hashtable.h"
#include <iostream>

int main()
{
    // REPL repl;
    HashTable ht;

    ht.insert('A', 4);
    ht.insert('B', 5);
    ht.insert('C', 3);
    ht.insert('D', 9);

    std::cout << ht.search('A') << std::endl;

    ht.printTable();

    ht.remove('A');

    ht.printTable();

    if (ht.is_empty())
        std::cout << "Empty" << std::endl;
    else
        std::cout << "Not empty" << std::endl;
    return 0;
}
