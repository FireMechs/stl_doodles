// LinkedList.cpp

#include <stdlib.h>
#include <exception>
#include <stdexcept>

#include "LinkedList.h"

// Default constructor, the list is empty to start
/*
 * throw -> brings up an exception for catch
 *
 * */
LinkedList::LinkedList() {
    /*
     * Instance of this class creates an empty linked list
     * with the head being the tail also pointing to NULL
     *
     * */
    _headPtr = nullptr;//
}

// Default destructor, must delete all nodes

LinkedList::~LinkedList() {
    /*
     * free the head pointer
     * */
    delete[] _headPtr;
}

// Add a node containing "value" to the front

void LinkedList::InsertFront(double value) {
    /*
     * 1-> Create a node instance
     * 2-> Assign data to the instance {
     *      node's value = new value;
     *      node's next ptr = existing head ptr
     * }
     * 3-> existing head_ptr = new node
     * */
    Node *newNode = new Node();
    newNode->data = value;// assign the value to the new Node
    newNode->next = _headPtr;// new Node's next is the current head
    _headPtr = newNode;
}

// Add a node containing "value" to position "index"

void LinkedList::Insert(double value, unsigned int index) {
    /*
     * 1-> if(index is less than 0 or index is greater than (list's size + 1)){
     *      throw error
     * }
     * 2-> Instance of the node (new node)
     * 3-> Initialize new node{
     *      node's value = new value
     *      node's next = NULL // not established yet
     * }
     * 4-> if(existing list is empty){
     *      insert the new node at beginning
     * }
     * 5-> else if (index is = 0){
     *      new node's next = existing head ptr
     *      existing head ptr = new node's instance
     * }else{
     *      // iterate to index (while keeping count just ahead of the index)and insert
     *      nodes ptr = existing head ptr
     *      initialize count to 1 // to keep ahead of the index
     *      while(nodes ptr is not = NULL(end)){
     *          if(count is = index){
     *              new node's instance next = nodes ptr next
     *              nodes ptr next = new node's instance
     *              break
     *          }
     *          nodes ptr = nodes ptr next
     *          increment count by 1
     *      }
     * }*/
    // check the index
    if((index < 0) || (index > (GetLength() + 1)))
        throw std::invalid_argument("Wrong index");

    Node *temp_node = new Node();
    temp_node->data = value;
    temp_node->next = nullptr;

    if(_headPtr == nullptr)//list is empty
        _headPtr = temp_node;
    else if(index == 0)
    {
        temp_node->next = _headPtr;
        _headPtr = temp_node;
    }
    else
    {
        Node *cur = _headPtr;
        int count = 1;
        while(cur != nullptr)
        {
            if(count == index)
            {
                temp_node->next = cur->next;
                cur->next = temp_node;
                break;
            }
            cur = cur->next;
            count++;
        }
    }
}


// Return value at position "index"

double LinkedList::GetNode(unsigned int index) {
    /*
     * // get node at index
     * 1-> initialize current node with the existing head ptr
     * 2-> initialize count with 0
     * 3-> while(current node is not = end){
     *      if(count is = index){
     *          return current node's data
     *      }else{
     *          increment count by 1
     *          increment current node
     *      }
     * }
     * 4-> if end throw an error(not found)
     * */
    Node *curr_node = _headPtr;// node_iterator
    int curr_index  = 0;// index of  current  node
    //loop
    while(curr_node != nullptr){// NULL is the end of the pointer
        if(curr_index == index){
            return curr_node->data;// return the current_node's data
        }
        curr_index++;
        curr_node = curr_node->next;// increment the node
    }
    // at this point-> index if not available
    throw std::invalid_argument("Wrong index");
}


// Return the index of the node containing "value"

unsigned int LinkedList::Search(double value) {
    /*
     * 1-> Initialize current node's pointer with the existing head pointer
     * 2-> Initialize count with 0
     * 3-> while(current node is not = end){
     *      if(current node data is equal to requested data){
     *          return index of current node (equals to count at this point)
     *      }else{
     *          increment count by 1
     *          increment current node's pointer
     *      }
     * }*/
    Node *curr_node = _headPtr;
    int count = 0;//iterator counter
    while(curr_node != nullptr){
        if(curr_node->data == value){
            return count;
        }
        ++count;
        curr_node = curr_node->next;//increment
    }
    // no match
    throw std::invalid_argument("No Match");
}


// Delete the node at position "index", return the value that was there

double LinkedList::DeleteNode(unsigned int index) {
    /*
     * 1-> if(list is empty){
     *      // nothing to delete
     *      throw an error
     * }
     * 2-> Initialize current node's pointer with existing head pointer
     * 3-> If(requested index is = 0){
     *      replace existing head pointer with current nodes's next
     *      get data of the current node
     *      free current node(points it to NULL)
     *      return the acquired data
     * }
     * // get the previous node of the node requested at index
     * 4-> Initialize count with 0
     * 5-> while(curr_node is not = end and count is less than (index -1) ){
     *      increment count  by 1
     *      increment index
     * }
     * 6->if(curr_node is = end){// point to end after looping
     *      throw an error
     * }
     * 7-> Get a pointer of the next of current node's next
     * 8-> Get data of the current node's pointer
     * 9-> Free Current node's next
     * 10-> return data of the current node
     * */
    // case 1 :list is empty
    if(_headPtr == nullptr)
        throw std::invalid_argument("Empty list");
    // case 2: list != empty
    Node *curr_node = _headPtr;
    // if head is to be removed
    if(index == 0){
        _headPtr = curr_node->next;
        double temp_data = curr_node->data;
        free(curr_node);
        return temp_data;
    }
    // previous node of the node at index
    int i = 0;
    while((curr_node != nullptr)&&( i < (index - 1))){
        i++;
        curr_node = curr_node->next;
    }
    // if index == size of list
    if(curr_node == nullptr  || curr_node->next == nullptr)
        throw std::invalid_argument("Wrong index");
    // get ahead of the node to be deleted
    Node *curr_node_next_next = curr_node->next->next;
    //delete
    double _temp_data = curr_node->data;
    free(curr_node->next);
    curr_node->next = curr_node_next_next;
    return _temp_data;
}

// This function reverses the order of all nodes so the first node is now the
// last and the last is now the first (and all between). So a list containing
// (4, 0, 2, 11, 29) would be (29, 11, 2, 0, 4) after Reverse() is called.

void LinkedList::Reverse() {
    // reversing = (saving previous and current) and store current at previous
    /*
     * 1-> if (list is empty){
     *      throw an error
     * }
     * 2-> Create 3 node instances (previous, current and next) and initialize them with null
     * 3-> Current  node instance is existing head ptr
     * while(curr node is not at the end){
     *      next = current node's next
     *      current node's next = previous node // points to null
     *      previous node= current node
     *      current node = next node
     * }
     * 4-> Finally head pointer points to last(previous node)
     * */
    if(_headPtr == nullptr){
        throw std::invalid_argument("Empty");// empty list
    }
    Node *prev = nullptr;
    Node *curr = nullptr;
    Node *next = nullptr;
    curr = _headPtr;
    while(curr != nullptr){
        next = curr->next;// next stored
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    _headPtr = prev;// head point to last
}

// Return the number of nodes in the list

int LinkedList::GetLength() {
    //iterative method
    /*
     * Iterate through to end while keeping the count
     *
     * */
    int length = 0;
    Node *curr_head = _headPtr;
    while(curr_head != nullptr){
        length++;
        curr_head = curr_head->next;
    }
    return length;
}