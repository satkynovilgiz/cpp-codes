/*
 * Name: Ilgiz Satkynov
 * Course: CIS D022C - Data Abstraction & Structures
 * Assignment: Lab 3: Hash Tables
 * Description: Implements a basic Hash Table class using a fixed-size array.
 *              Uses linear probing for collision handling and maps keys using
 *              the formula: index = key % table_size.
 */

#include <iostream>

using namespace std;

// Class representation of a single Key-Value pair (Hash Node)
class HashNode {
public:
    int key;
    int value;

    HashNode(int k, int v) {
        key = k;
        value = v;
    }
};

// Main Hash Table Class implemented using an Array
class HashTable {
private:
    static const int TABLE_SIZE = 10; // Defined size of the hash table array
    HashNode** table;                 // Array of pointers to HashNodes

public:
    HashTable() {
        table = new HashNode*[TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }

    // Destructor to safely clean up dynamic memory from the heap
    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i] != nullptr) {
                delete table[i];
            }
        }
        delete[] table;
    }

    // Hash Function using the formula: index = key % table_size
    int hashFunction(int key) const {
        return key % TABLE_SIZE;
    }

    // insert(key, value): Adds a key-value pair using linear probing for collisions
    void insert(int key, int value) {
        int hashIndex = hashFunction(key);
        int originalIndex = hashIndex;

        // Linear probing: Look for an empty slot or a slot with the matching key to update
        while (table[hashIndex] != nullptr && table[hashIndex]->key != key) {
            hashIndex = (hashIndex + 1) % TABLE_SIZE;
            
            // If we loop all the way around, the table is full
            if (hashIndex == originalIndex) {
                cout << "Hash Table is Full! Cannot insert key: " << key << endl;
                return;
            }
        }

        // If slot is occupied by the same key, update the value. Otherwise, create new node.
        if (table[hashIndex] != nullptr) {
            table[hashIndex]->value = value;
        } else {
            table[hashIndex] = new HashNode(key, value);
        }
    }

    // retrieve(key): Retrieves the value associated with a key, returns -1 if not found
    int retrieve(int key) const {
        int hashIndex = hashFunction(key);
        int originalIndex = hashIndex;

        while (table[hashIndex] != nullptr) {
            if (table[hashIndex]->key == key) {
                return table[hashIndex]->value;
            }
            hashIndex = (hashIndex + 1) % TABLE_SIZE;
            
            if (hashIndex == originalIndex) {
                break;
            }
        }
        return -1; // Return -1 if the key does not exist
    }

    // Helper method to explicitly show the calculated hash index for testing requirements
    void printHashIndex(int key) const {
        cout << "Key: " << key << " -> Calculated Index: " << hashFunction(key) << endl;
    }
};

// MAIN SYSTEM DEMONSTRATION
int main() {
    HashTable myHashTable;

    cout << "==========================================================" << endl;
    cout << "                  LAB 3: HASH TABLES                      " << endl;
    cout << "==========================================================" << endl;

    // PART 2: Testing the Hash Function Indices
    cout << "--- Part 2: Calculating Hash Function Indices ---" << endl;
    myHashTable.printHashIndex(10);
    myHashTable.printHashIndex(20);
    myHashTable.printHashIndex(35);
    cout << "----------------------------------------------------------" << endl;

    // PART 1: Testing Insertion and Retrieval Operations
    cout << "\n--- Part 1: Testing Insertion and Retrieval ---" << endl;
    
    // Inserting elements
    myHashTable.insert(10, 100);
    myHashTable.insert(20, 200); // Will cause a collision with key 10 and resolve via Linear Probing
    myHashTable.insert(35, 350);

    cout << "Inserting key-value pairs..." << endl;
    cout << "Retrieving value for key 10: " << myHashTable.retrieve(10) << endl;
    cout << "Retrieving value for key 20: " << myHashTable.retrieve(20) << endl;
    cout << "Retrieving value for key 35: " << myHashTable.retrieve(35) << endl;
    cout << "Retrieving value for non-existent key 99: " << myHashTable.retrieve(99) << endl;
    
    cout << "==========================================================" << endl;

    return 0;
}