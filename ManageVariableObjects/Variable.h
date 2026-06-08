/*
 * Name: Ilgiz Satkynov
 * File: Variable.h
 * Description: Class specification managing an individual variable's name and value.
 */

#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>

class Variable {
private:
    std::string name;
    int value;

public:
    // Requirement 16: No default constructor provided
    Variable(std::string inName, int inValue);
    
    std::string getName() const;
    int getValue() const;
    void setValue(int inValue);
};

#endif