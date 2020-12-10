//
// Created by mew on 09/12/2020.
//

#include "tigger.hpp"

#include <utility>

TVarDecl::TVarDecl(TVariable* name, int value) : name(name), value(value) {}

string TVarDecl::to_string()
{
    return name->to_string() + " = " + std::to_string(value);
}


TArrayDecl::TArrayDecl(TVariable* name, int size) : name(name), size(size) {}

string TArrayDecl::to_string()
{
    return name->to_string() + " = malloc " + std::to_string(size);
}

TVariable::TVariable(string name, bool is_array) : name(std::move(name)), is_array(is_array) {}

string TVariable::to_string()
{
    return name;
}