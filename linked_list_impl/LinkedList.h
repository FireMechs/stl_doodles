// LinkedList.h

#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include <iostream>
using namespace std;

struct Node
{
    double data;
    Node* next;
};

class LinkedList
{
public:
    LinkedList();         // Default constructor, the list is empty to start
    ~LinkedList();        // Default destructor, must delete all nodes

    void InsertFront(double value); // Add a node containing "value" to the front
    void Insert(double value, unsigned int index); // Add a node containing "value" to position "index"

    double GetNode(unsigned int index); // Return value at position "index"
    unsigned int Search(double value); // Return the index of the node containing "value"

    double DeleteNode(unsigned int index); // Delete the node at position "index", return the value that was there

    // This function reverses the order of all nodes so the first node is now the
    // last and the last is now the first (and all between). So a list containing
    // (4, 0, 2, 11, 29) would be (29, 11, 2, 0, 4) after Reverse() is called.
    void Reverse();

    int GetLength();        // Return the number of nodes in the list

private:

    // Add class members here
    Node *_headPtr;// instance of the class Node;
    int _size = 0;// linked list size
};
#endif
