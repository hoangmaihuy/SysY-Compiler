#pragma once
#include "globals.hpp"

class TStmt
{
public:
    virtual string to_string() = 0;
    virtual void generate_riscv(vector<string>& riscv_list);
};

class TValue : public TStmt
{
public:
    virtual string to_string() = 0;
};

class TComment : public TStmt
{
public:
    string comment;
    TComment(string comment);
    string to_string() override;
};

class TVarDecl : public TStmt
{
public:
    string name;
    int value;
    TVarDecl(string name, int value=0);
    string to_string() override;
    virtual void generate_riscv(vector<string>& riscv_list);
};

class TArrayDecl : public TStmt
{
public:
    string name;
    int size;
    TArrayDecl(string name, int size);
    string to_string() override;
    virtual void generate_riscv(vector<string>& riscv_list);
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
    virtual void generate_riscv(vector<string>& riscv_list);
};

class TAssignOpReg : public TStmt
{
public:
    string res_reg;
    int op;
    string rhs_reg;
    TAssignOpReg(string res_reg, int op, string rhs_reg);
    string to_string() override;
    virtual void generate_riscv(vector<string>& riscv_list);
};

class TCopyReg : public TStmt
{
public:
    string res_reg;
    string value_reg;
    TCopyReg(string res_reg, string value_reg);
    string to_string() override;
    virtual void generate_riscv(vector<string>& riscv_list);
};

class TAssignNumber : public TStmt
{
public:
    string reg_name;
    int value;
    TAssignNumber(string reg_name, int value);
    string to_string() override;
    virtual void generate_riscv(vector<string>& riscv_list);
};

class TArrayWrite : public TStmt
{
public:
    string array_reg;
    int index;
    string value_reg;
    TArrayWrite(string array_reg, int index, string value_reg);
    string to_string() override;
    virtual void generate_riscv(vector<string>& riscv_list);
};

class TArrayRead : public TStmt
{
public:
    string res_reg;
    string array_reg;
    int index;
    TArrayRead(string res_reg, string array_reg, int index);
    string to_string() override;
    virtual void generate_riscv(vector<string>& riscv_list);
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
    virtual void generate_riscv(vector<string>& riscv_list);
};

class TUnconditionalJump : public TStmt
{
public:
    string label;
    TUnconditionalJump(string label);
    string to_string() override;
    virtual void generate_riscv(vector<string>& riscv_list);
};

class TLabel : public TStmt
{
public:
    string label;
    TLabel(string label);
    string to_string() override;
    virtual void generate_riscv(vector<string>& riscv_list);
};

class TFuncCall : public TStmt
{
public:
    string func_name;
    TFuncCall(string func_name);
    string to_string() override;
    virtual void generate_riscv(vector<string>& riscv_list);
};

class TStoreStack : public TStmt
{
public:
    string reg_name;
    int loc;
    TStoreStack(string reg_name, int loc);
    string to_string() override;
    virtual void generate_riscv(vector<string>& riscv_list);
};

class TLoadStack : public TStmt
{
public:
    string reg_name;
    int loc;
    TLoadStack(int loc, string reg_name);
    string to_string() override;
    virtual void generate_riscv(vector<string>& riscv_list);
};

class TLoadGlobal : public TStmt
{
public:
    string var_name;
    string reg_name;
    TLoadGlobal(string var_name, string reg_name);
    string to_string() override;
    virtual void generate_riscv(vector<string>& riscv_list);
};

class TLoadaddrStack : public TStmt
{
public:
    string reg_name;
    int loc;
    TLoadaddrStack(int loc, string reg_name);
    string to_string() override;
    virtual void generate_riscv(vector<string>& riscv_list);
};

class TLoadaddrGlobal : public TStmt
{
public:
    string var_name;
    string reg_name;
    TLoadaddrGlobal(string var_name, string reg_name);
    string to_string() override;
    virtual void generate_riscv(vector<string>& riscv_list);
};

class TReturn : public TStmt
{
public:
    string to_string() override;
    virtual void generate_riscv(vector<string>& riscv_list);
};

class TFuncDef : public TStmt
{
public:
    string func_name;
    int args_num;
    int stack_size;
    TFuncDef(string func_name, int args_num, int stack_size);
    string to_string() override;
    virtual void generate_riscv(vector<string>& riscv_list);
};

class TFuncEnd : public TStmt
{
public:
    string func_name;
    TFuncEnd(string func_name);
    string to_string() override;
    virtual void generate_riscv(vector<string>& riscv_list);
};
