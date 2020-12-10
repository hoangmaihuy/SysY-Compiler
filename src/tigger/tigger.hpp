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

class TVarDecl : public TStmt
{
public:
    string name;
    int value;
    TVarDecl(string name, int value=0);
    string to_string() override;
};

class TArrayDecl : public TStmt
{
public:
    string name;
    int size;
    TArrayDecl(string name, int size);
    string to_string() override;
};

class TAssignRegOpReg : public TStmt
{
public:
    string res_reg;
    string lhs_reg;
    int op;
    string rhs_reg;
    TAssignRegOpReg(string res_reg, string lhs_reg, int op, string rhs_reg);
    string to_string() override;
};

class TAssignOpReg : public TStmt
{
public:
    string res_reg;
    int op;
    string rhs_reg;
    TAssignOpReg(string res_reg, int op, string rhs_reg);
    string to_string() override;
};

class TCopyReg : public TStmt
{
public:
    string res_reg;
    string value_reg;
    TCopyReg(string res_reg, string value_reg);
    string to_string() override;
};

class TAssignNumber : public TStmt
{
public:
    string reg_name;
    int value;
    TAssignNumber(string reg_name, int value);
    string to_string() override;
};

class TArrayWrite : public TStmt
{
    string array_reg;
    int index;
    string value_reg;
    TArrayWrite(string array_reg, int index, string value_reg);
    string to_string() override;
};

class TArrayRead : public TStmt
{
public:
    string res_reg;
    string array_reg;
    int index;
    TArrayRead(string res_reg, string array_reg, int index);
    string to_string() override;
};

class TConditionalJump : public TStmt
{
public:
    string reg_1;
    int op;
    string reg_2;
    string label;
    TConditionalJump(const string &reg1, int op, const string &reg2, const string& label);
    string to_string() override;
};

class TUnconditionalJump : public TStmt
{
public:
    string label;
    TUnconditionalJump(string label);
    string to_string() override;
};

class TLabel : public TStmt
{
public:
    string label;
    TLabel(string label);
    string to_string() override;
};

class TFuncCall : public TStmt
{
public:
    string func_name;
    TFuncCall(string func_name);
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

class TLoadGlobal : public TStmt
{
public:
    string var_name;
    string reg_name;
    TLoadGlobal(string var_name, string reg_name);
    string to_string() override;
};

class TLoadaddrStack : public TStmt
{
public:
    string reg_name;
    int loc;
    TLoadaddrStack(int loc, string reg_name);
    string to_string() override;
};

class TLoadaddrGlobal : public TStmt
{
public:
    string var_name;
    string reg_name;
    TLoadaddrGlobal(string var_name, string reg_name);
    string to_string() override;
};

class TStoreRegArray : public TStmt
{
public:
    string res_reg;
    int index;
    string value_reg;
    TStoreRegArray(string res_reg, int index, string value_reg);
    string to_string() override;
};

class TReturn : public TStmt
{
public:
    string to_string() override;
};
