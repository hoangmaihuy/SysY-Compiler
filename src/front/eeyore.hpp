#pragma once
#include "globals.hpp"

class EBase
{
public:
    virtual string to_string();
};

class EStmt : public EBase
{
public:
    virtual string to_string();
};

class EValue : public EStmt
{
public:
    virtual string to_string();
};

class EVariable : public EValue
{
public:
    string name;
    bool is_array;
    EVariable(string name, bool is_array=false);
    virtual string to_string();
};

class ERightVal : public EValue
{
public:
    bool is_number;
    int value;
    EValue* name;
    ERightVal(EValue* name);
    ERightVal(int value);
    virtual string to_string();
};

class ELeftVal : public EValue 
{
public: 
    bool is_array;
    EValue* name;
    EValue* index;
    ELeftVal(EValue* name, EValue* index=nullptr, bool is_array=false);
    virtual string to_string();
};

class EVarStmt : public EStmt
{
public:
    EValue* name;
    EVarStmt(string name);
    EVarStmt(EValue* name);
    virtual string to_string();
};

class EVarArrayStmt : public EStmt 
{
public:
    EVariable* name;
    int size;
    EVarArrayStmt(string name, int size);
    virtual string to_string();
};

class EAssignStmt : public EStmt
{
public:
    EValue* res;
    EValue* value;
    EAssignStmt(string name, int value);
    EAssignStmt(string name, EValue* value);
    EAssignStmt(EValue* res, int value);
    EAssignStmt(EValue* res, EValue* value);
    virtual string to_string();
};

class EBinaryExpr : public EStmt
{
public:
    EValue* res;
    EValue* lhs;
    int op;
    EValue* rhs;
    EBinaryExpr(EValue* res, EValue* lhs, int op, EValue* rhs);
    virtual string to_string();
};

class EUnaryExpr : public EStmt 
{
public:
    EValue* res;
    int op;
    EValue* rhs;
    EUnaryExpr(EValue* res, int op, EValue* rhs);
    virtual string to_string();
};

class EParamStmt : public EStmt 
{
public:
    EValue* name;
    EParamStmt(EValue* name);
    virtual string to_string();
};

class EFuncCall : public EValue 
{
public:
    string func_name;
    EFuncCall(string func_name);
    virtual string to_string();
};

class EJumpLabel : public EStmt 
{
public:
    string label;
    EJumpLabel(string label);
    virtual string to_string();
};

class EUnconditionalJump : public EStmt 
{
public:
    string label;
    EUnconditionalJump(string label);
    virtual string to_string();
};

class EConditionalJump : public EStmt 
{
public:
    string label;
    EValue* cond_name;
    bool cond_value;
    EConditionalJump(string label, EValue* cond_name, bool cond_value);
    virtual string to_string();
};

class EReturnStmt : public EStmt
{
public:
    EValue* value;
    EReturnStmt(EValue* value=nullptr);
    virtual string to_string();
};

