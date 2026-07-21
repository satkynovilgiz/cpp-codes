/*
 * Name: Ilgiz Satkynov
 * Course: CIS D022C - Data Abstraction & Structures
 * Assignment: Lab 2.1 - Link-Based Data Structure
 * Description: Demonstrates dynamic memory allocation with singly linked lists.
 * Part 1 builds a list in reverse order using front insertion.
 * Part 2 builds a list in forward order using a trailing tail pointer.
 * Part 3 fixes structural syntax loops in a standard traversal print function.
 */

#include <iostream>
#include <string>

using namespace std;

// Define the foundational structural unit for a singly linked list
struct Node {
    string data;
    Node* next;
};

// QUESTION 2: CORRECTED PRINT FUNCTION (Bug Free Implementation)
void printList(Node* head) {
    // Fixed: Removed the premature infinite-loop semicolon after the while statement.
    // Fixed: Migrated legacy macro 'NULL' over to modern 'nullptr'.
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next; // Progress to the consecutive link block element safely
    }
    cout << endl;
}

// Helper function to deallocate memory and prevent memory leaks
void clearList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    cout << "==========================================================" << endl;
    cout << "         LAB 2.1 - LINK-BASED DATA STRUCTURES             " << endl;
    cout << "==========================================================" << endl;

    // QUESTION 1 (Part a): Build in Reverse Order (Front Insertion)
    cout << "\n--- Part (a): Building List in Reverse Order (C -> B -> A) ---" << endl;
    
    Node* headReverse = nullptr;
    Node* newNode = nullptr;

    // Step 2: Create node for "C"
    newNode = new Node;
    newNode->data = "C";
    newNode->next = nullptr;
    headReverse = newNode;

    // Step 3: Create node for "B" and insert at the front
    newNode = new Node;
    newNode->data = "B";
    newNode->next = headReverse;
    headReverse = newNode;

    // Step 4: Create node for "A" and insert at the front
    newNode = new Node;
    newNode->data = "A";
    newNode->next = headReverse;
    headReverse = newNode;

    cout << "Resulting Front Insertion List Output: ";
    printList(headReverse);


    // QUESTION 1 (Part b): Build in Forward Order (Tail Pointer Insertion)
    cout << "\n--- Part (b): Building List in Forward Order (A -> B -> C) ---" << endl;
    
    Node* headForward = nullptr;

    // Step 2: Create first node "A"
    newNode = new Node;
    newNode->data = "A";
    newNode->next = nullptr;
    headForward = newNode;

    // Step 3: Track the last node using a tail pointer
    Node* tail = headForward;

    // Step 4: Create node "B" and attach to the end
    newNode = new Node;
    newNode->data = "B";
    newNode->next = nullptr;
    tail->next = newNode;
    tail = newNode;

    // Step 5: Create node "C" and attach to the end
    newNode = new Node;
    newNode->data = "C";
    newNode->next = nullptr;
    tail->next = newNode;
    tail = newNode;

    cout << "Resulting Tail Insertion List Output : ";
    printList(headForward);
    cout << "\n==========================================================" << endl;

    // Clean up dynamic memory from heap allocations
    clearList(headReverse);
    clearList(headForward);

    return 0;
}