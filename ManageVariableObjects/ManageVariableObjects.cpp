/*
 * Name: Ilgiz Satkynov
 * File: ManageVariableObjects.cpp
 * Description: Menu driver loop processing commands, handling line stream extractions, and input validation.
 */

#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include "VariableListManager.h"

using namespace std;

// Prototypes tracking functional modular design criteria
bool isValidVariableName(const string& name);
void processCommand(const string& line, VariableListManager& manager, bool& keepRunning);

int main() {
    VariableListManager manager;
    string currentLine;
    bool keepRunning = true;

    // Requirement 1: Matches opening prompt string exactly
    cout << "Please enter variable assignment, variable name only or list or exit:" << endl;

    while (keepRunning && getline(cin, currentLine)) {
        if (!currentLine.empty()) {
            processCommand(currentLine, manager, keepRunning);
        }
    }

    return 0;
}

// Requirement 6 & 11: Single return point checking digit rules
bool isValidVariableName(const string& name) {
    bool valid = true;
    if (name.empty() || isdigit(name[0])) {
        valid = false;
    }
    return valid;
}

void processCommand(const string& line, VariableListManager& manager, bool& keepRunning) {
    stringstream ss(line);
    string token1, token2, token3;

    ss >> token1;

    if (token1 == "exit") {
        cout << "Exiting..." << endl;
        keepRunning = false;
    } 
    else if (token1 == "list") {
        manager.printAllVariables();
    } 
    else {
        // Check if this is an assignment statement: var = value
        if (ss >> token2 && token2 == "=") {
            if (!isValidVariableName(token1)) {
                // Fix: Only display syntax rule warnings for broken assignments (e.g., 1count = 10)
                cout << "Invalid variable name. Cannot start with a digit." << endl;
            } 
            else if (ss >> token3) {
                // Assess whether the right-hand value is numeric or another variable identifier
                if (isdigit(token3[0]) || (token3[0] == '-' && token3.size() > 1 && isdigit(token3[1]))) {
                    int numericValue = stoi(token3);
                    manager.assignVariableValue(token1, numericValue);
                } else {
                    manager.assignVariableWithVariable(token1, token3);
                }
            }
        } else {
            // Fix: If it's a standalone lookup (like 1count), just let it safely display "Undefined" 
            manager.displayVariable(token1);
        }
    }
}gitngigigitini