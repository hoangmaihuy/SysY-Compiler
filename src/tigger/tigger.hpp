#pragma once
#include "globals.hpp"

class TStmt
{
public:
    virtual string to_string() = 0;
};

class TValue : public TStmt
{
public:
    virtual string to_string() = 0;
};

class TNumber : public TValue
{
public:
    int value;
    TNumber(int value);
    virtual string to_string();
};

class TVariable : public TValue
{
public:
    string name;
    bool is_array;
    TVariable(string name, bool is_array);
    string to_string() override;
};

class TRegister : public TValue
{
public:
    string reg_name;
    explicit TRegister(string reg_name);
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

class TStoreStack : public TStmt
{
public:
    string reg_name;
    int loc;
    TStoreStack(string reg_name, int loc);
    string to_string() override;
};

class TLoadStack : public TStmt
{
public:
    string reg_name;
    int loc;
    TLoadStack(int loc, string reg_name);
    string to_string() override;
};
