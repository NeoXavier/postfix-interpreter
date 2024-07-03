#include <string>

using namespace std;

class Node {
public:
    string key;
    int value;
    Node* next;

    Node(string key, int value)
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

    // Function to insert a
    // node at the end of the
    // linked list.
    void insertNode(string& key, int& value);

    // Function to print the
    // linked list.
    void printList();

    // Function to delete the
    // node at given position
    void deleteNode(string& key);

    bool isEmpty() { return head == nullptr; };
};
