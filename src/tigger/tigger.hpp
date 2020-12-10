#pragma once
#include "globals.hpp"

class TStmt
{
public:
    virtual string to_string() = 0;
};

class TVariable : public TStmt
{
public:
    string name;
    bool is_array;
    TVariable(string name, bool is_array);
    string to_string() override;
};

class TVarDecl : public TStmt
{
public:
    TVariable* name;
    int value;
    explicit TVarDecl(TVariable* name, int value=0);
    string to_string() override;
};

class TArrayDecl : public TStmt
{
public:
    TVariable* name;
    int size;
    TArrayDecl(TVariable* name, int size);
    string to_string() override;
};

