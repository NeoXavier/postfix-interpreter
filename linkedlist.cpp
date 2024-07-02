#include "linkedlist.h"
#include <iostream>

LinkedList::LinkedList()
{
    head = nullptr;
}

/* Inserts node at end of list */
void LinkedList::insertNode(string key, int value)
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
        cout << temp->key << " " << temp->value << endl;
        temp = temp->next;
    }
}

void LinkedList::deleteNode(string key)
{
    // If LinkedList is empty
    if (isEmpty()) {
        cout << "List is empty" << endl;
        return;
    }

    Node* temp = head;
    // First node itself is the node to be deleted
    if (temp->key == key) {
        head = temp->next;
        delete temp;
        return;
    }

    // Search for node to be deleted
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
    return;
}
