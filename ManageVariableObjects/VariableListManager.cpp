/*
 * Name: Ilgiz Satkynov
 * File: VariableListManager.cpp
 * Description: Implementation of the VariableListManager class managing searching, assignments, and displays.
 */

#include <iostream>
#include "VariableListManager.h"

// Destructor ensures zero memory leaks by releasing heap allocations
VariableListManager::~VariableListManager() {
    for (size_t i = 0; i < varList.size(); i++) {
        delete varList[i];
    }
    varList.clear();
}

// Requirement 11 & 12: Single-return loop tracking elements without scanning past matches
Variable* VariableListManager::findVariable(const std::string& name) const {
    Variable* target = nullptr;
    size_t i = 0;
    
    while (i < varList.size() && target == nullptr) {
        if (varList[i]->getName() == name) {
            target = varList[i];
        }
        i++;
    }
    return target;
}

// Requirement 1 & 4: Matches the exact output style of the prompt sample run
void VariableListManager::displayVariable(const std::string& name) const {
    Variable* var = findVariable(name);
    if (var != nullptr) {
        std::cout << var->getName() << "(" << var->getValue() << ")" << std::endl;
    } else {
        std::cout << "Undefined" << std::endl;
    }
}

void VariableListManager::assignVariableValue(const std::string& name, int value) {
    Variable* var = findVariable(name);
    if (var != nullptr) {
        var->setValue(value);
    } else {
        // Requirement 5: Create objects outside the vector using the "new" operator
        Variable* newVar = new Variable(name, value);
        varList.push_back(newVar);
    }
    // Fix: Echo the updated variable to the terminal to match sample output
    displayVariable(name);
}

void VariableListManager::assignVariableWithVariable(const std::string& destName, const std::string& srcName) {
    Variable* srcVar = findVariable(srcName);
    if (srcVar != nullptr) {
        assignVariableValue(destName, srcVar->getValue());
    } else {
        std::cout << "Undefined" << std::endl;
    }
}

void VariableListManager::printAllVariables() const {
    for (size_t i = 0; i < varList.size(); i++) {
        std::cout << varList[i]->getName() << "(" << varList[i]->getValue() << ")" << std::endl;
    }
    // Requirement 13: Utilize internal vector sizing rather than tracking a separate counter
    std::cout << "Number of variables: " << varList.size() << std::endl;
}