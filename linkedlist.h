#include <string>

using namespace std;

class Node {
public:
    string key;
    int value;
    Node* next;

    Node(string key, double value)
        : key(key)
        , value(value)
        , next(nullptr)
    {
    }
};

class LinkedList {
public:
    Node* head;

    // Default constructor
    LinkedList();

    // Insert a node at the end of the linked list.
    void insertNode(string& key, double value);

    // Deletes a node with the given key.
    void deleteNode(string& key);

    // Prints the linked list.
    void printList();

    bool isEmpty() { return head == nullptr; };
};
