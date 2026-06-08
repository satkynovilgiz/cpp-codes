/*
 * Name: Ilgiz Satkynov
 * File: Variable.cpp
 * Description: Implementation of the Variable class member functions.
 */

#include "Variable.h"

Variable::Variable(std::string inName, int inValue) {
    name = inName;
    value = inValue;
}

std::string Variable::getName() const {
    return name;
}

int Variable::getValue() const {
    return value;
}

void Variable::setValue(int inValue) {
    value = inValue;
}