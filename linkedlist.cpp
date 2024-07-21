#include "linkedlist.h"
#include <iostream>

LinkedList::LinkedList()
{
    head = nullptr;
}

/* Inserts node at end of list */
/*
 * Pseudocode

 insertNode(key, value)
    newNode = Node(key, value)
    if HEAD = NIL
        HEAD = newNode
        return
    last = HEAD
    while last.next != NIL
        last = last.next
    last.next = newNode
    newNode.next = NIL
    return

 */
void LinkedList::insertNode(string& key, double value)
{
    // Create new node to be inserted
    Node* newNode = new Node(key, value);

    // If LinkedList is empty
    if (head == nullptr) {
        head = newNode;
        return;
    }

    // Traverse to end of list
    Node* last = head;
    while (last->next != nullptr) {
        last = last->next;
    }

    // Set next pointer of last node to new node
    last->next = newNode;

    // Set next pointer of new node to nullptr
    newNode->next = nullptr;

    return;
}

void LinkedList::printList()
{
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->key << " " << temp->value << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

/*
 * Pseudocode

 deleteNode(key)
    if linkedlist is empty
        print(”List is empty”)
        return
    Initalise temp to HEAD
    if temp.key = key
        HEAD = temp.next
        return
    left = HEAD
    while temp!= NIL and temp.key!= key
        left = temp
        temp = temp.next
    if temp = NIL
        print(”Node not found”)
        return
    prev.next = curr.next
    Delete node at temp
    return

 */
void LinkedList::deleteNode(string& key)
{
    // If LinkedList is empty
    if (isEmpty()) {
        cout << "List is empty" << endl;
        return;
    }

    // Initalize temp to HEAD
    Node* temp = head;

    // First node itself is the node to be deleted
    if (temp->key == key) {
        head = temp->next;
        delete temp;
        cout << "Key deleted" << endl;
        return;
    }

    // Search for node to be delete
    // Initalize left to HEAD
    Node* left = head;
    while (temp != nullptr && temp->key != key) {
        left = temp;
        temp = temp->next;
    }

    // If while loop was exited because temp is nullptr
    if (temp == nullptr) {
        cout << "Node not found" << endl;
        return;
    }

    // Set next pointer of left node to the next node
    left->next = temp->next;
    // Delete node
    delete temp;
    cout << "Key deleted" << endl;
    return;
}
