// main.cpp

#include "LinkedList.h"


int main() {
    cout << "Creating a Linked List." << endl;

    LinkedList myList;
    double x;

    try {
        myList.InsertFront(3.0);
    }    catch (...) {
        cout << "InsertFront 1 failed" << endl;
    }
    try {
        myList.Insert(4.0, 0);
        myList.Insert(5.0, 2);
        myList.Insert(6.0, 1);
    } catch (...) {
        cout << "Insert failed" << endl;
    }
    try {
        myList.Insert(7.0, 6);
        cout << "Insert should have failed" << endl;
    } catch (...) {
        cout << "Insert failed appropriately" << endl;
    }

    try {
        myList.InsertFront(8.0);
    }    catch (...) {
        cout << "InsertFront 2 failed" << endl;
    }

    cout << myList.GetNode(0) << " (8)" << endl;
    cout << myList.GetNode(4) << " (5)" << endl;

    try {
        x = myList.GetNode(5);
        cout << "GetNode should have failed, returned " << x << endl;
    } catch (...) {
        cout << "GetNode failed appropriately" << endl;
    }

    cout << myList.Search(5.0) << " (4)" << endl;
    cout << myList.Search(4.0) << " (1)" << endl;

    try {
        x = myList.Search(-1.0) ;
        cout << "Search should have failed, returned " << x << endl;
    } catch (...) {
        cout << "Search failed appropriately" << endl;
    }

    cout << myList.DeleteNode(0) << " (8)" << endl;
    cout << myList.DeleteNode(3) << " (5)" << endl;

    try {
        x = myList.DeleteNode(16);
        cout << "DeleteNode should have failed, returned " << x << endl;
    }    catch (...) {
        cout << "DeleteNode failed appropriately" << endl;
    }

    myList.InsertFront(9.0);
    myList.InsertFront(10.0);

    cout << myList.GetLength() << " (5)" << endl;

    try {
        myList.Reverse();
    } catch (...) {
        cout << "Reverse failed" << endl;
    }

    for (int i = 0; i < myList.GetLength(); i++) {
        cout << myList.GetNode(i) << ", ";
    }

    cout << " (3, 6, 4, 9, 10)" << endl;

    cout << "Finished" << endl;

    return 0;
}
