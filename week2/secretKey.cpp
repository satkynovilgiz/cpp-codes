// Name: Ilgiz Satkynov 
// Date: April 15, 2026
// Assignment: Week 1, Question #1
// Description: Function to read a secret key with up to 3 verification attempts.
//Returns the key via return type and tries via pass-by-reference.

#include <iostream>
using namespace std;

// Function to read and verify the secret key
int readSecretKey(int &tries) {
    int key, verifyKey;
    int finalValue = 0; // Default to 0 if unsuccessful
    tries = 0;

    cout << "Please enter the key:    ";
    cin >> key;

    // Loop for verification attempts (limit 3)
    while (tries < 3 && finalValue == 0) {
        tries++;
        cout << "Please re-enter the key: ";
        cin >> verifyKey;

        if (key == verifyKey) {
            finalValue = key;
        } else {
            if (tries < 3) {
                cout << "Unmatched. ";
            }
        }
    }

    return finalValue; // Single return statement at the end
}

int main() {
    int triesAttempted;
    int resultKey = readSecretKey(triesAttempted);

    cout << "Key: " << resultKey << "  Number of tries: " << triesAttempted << endl;

    return 0;
}