// Name: Ilgiz Satkynov
// Date: April 21, 2026
// Assignment: Week 2: C-strings
// Description: Function to validate C-strings as hexadecimal numbers
// without using the C++ string class or string functions.

#include <iostream>
using namespace std;

// Helper function provided in the assignment hint
bool isHexaChar(char ch) {
    return ((ch >= '0') && (ch <= '9')) || 
           ((ch >= 'a') && (ch <= 'f')) || 
           ((ch >= 'A') && (ch <= 'F'));
}

// Requirement: Single return, no string class, one iteration only
bool isHexadecimal(const char hex[], bool &isPrefixed) {
    bool isValid = true;
    isPrefixed = false;
    int i = 0;

    // Check for empty string
    if (hex[0] == '\0') {
        isValid = false;
    } else {
        // Check for '0x' prefix
        if (hex[0] == '0' && hex[1] == 'x') {
            isPrefixed = true;
            i = 2; // Start checking digits after the '0x'
            
            // Invalid if nothing follows the '0x'
            if (hex[i] == '\0') {
                isValid = false;
            }
        }

        // Iterate through remaining characters
        while (hex[i] != '\0') {
            if (!isHexaChar(hex[i])) {
                isValid = false;
            }
            i++;
        }
    }

    return isValid;
}

// Function to handle testing logic
void testHex(const char hexStr[]) {
    bool isPrefixed = false;
    bool valid = isHexadecimal(hexStr, isPrefixed);
    
    cout << "Input: \"" << hexStr << "\"\tResult: " 
         << (valid ? "true" : "false") << " " 
         << (isPrefixed ? "true" : "false") << endl;
}

int main() {
    cout << "Testing Valid Hexadecimals:" << endl;
    testHex("0");       // true false
    testHex("0af");     // true false
    testHex("0xa");     // true true
    testHex("A");       // true false
    testHex("1F");      // true false

    cout << "\nTesting Invalid Hexadecimals:" << endl;
    testHex("");        // false false
    testHex("0x");      // false true
    testHex("1xa");     // false false
    testHex("1g");      // false false
    testHex("0xg");     // false true

    return 0;
}