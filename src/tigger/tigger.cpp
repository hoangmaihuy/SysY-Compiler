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

TNumber::TNumber(int value) : value(value) {}

string TNumber::to_string()
{
    return std::to_string(value);
}

TRegister::TRegister(string reg_name) : reg_name(std::move(reg_name)) {}

string TRegister::to_string()
{
    return reg_name;
}

TStoreStack::TStoreStack(string reg_name, int loc) : reg_name(std::move(reg_name)), loc(loc) {}

string TStoreStack::to_string()
{
    return "store " + reg_name + " " + std::to_string(loc);
}

TLoadStack::TLoadStack(int loc, string reg_name) : loc(loc), reg_name(std::move(reg_name)) {}

string TLoadStack::to_string()
{
    return "load " + std::to_string(loc) + " " + reg_name;
}

string TReturn::to_string()
{
    return "return";
}

TAssignRegNumber::TAssignRegNumber(string reg_name, int value) : reg_name(std::move(reg_name)), value(value)
{
}

string TAssignRegNumber::to_string()
{
    return reg_name + " = " + std::to_string(value);
}
