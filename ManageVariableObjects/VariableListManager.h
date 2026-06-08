/*
 * Name: Ilgiz Satkynov
 * File: VariableListManager.h
 * Description: Class specification managing a collection of Variable object pointers using a vector.
 */

#ifndef VARIABLE_LIST_MANAGER_H
#define VARIABLE_LIST_MANAGER_H

#include <vector>
#include <string>
#include "Variable.h"

class VariableListManager {
private:
    // Requirement 8 & 9: Private vector storing object pointers, hidden from main
    std::vector<Variable*> varList;
    
    // Internal helper function to minimize redundant code loops
    Variable* findVariable(const std::string& name) const;

public:
    ~VariableListManager(); // Cleans up dynamic pointer allocations
    
    void displayVariable(const std::string& name) const;
    void assignVariableValue(const std::string& name, int value);
    void assignVariableWithVariable(const std::string& destName, const std::string& srcName);
    void printAllVariables() const;
};

#endif