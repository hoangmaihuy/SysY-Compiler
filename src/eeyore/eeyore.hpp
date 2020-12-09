#pragma once
#include "globals.hpp"

enum EeyoreType
{
    E_BASE,
    E_STMT,
    E_VALUE,
    E_VARIABLE,
    E_RIGHT_VAL,
    E_LEFT_VAL,
    E_VAR_STMT,
    E_VAR_ARRAY_STMT,
    E_ASSIGN_STMT,
    E_BINARY_EXPR,
    E_UNARY_EXPR,
    E_PARAM,
    E_FUNC_CALL,
    E_FUNC_DEF,
    E_FUNC_END,
    E_UNCOND_JUMP,
    E_COND_JUMP,
    E_RETURN,
    E_LABEL
};

class EBase
{
public:
    virtual string to_string();
    virtual int get_type();
};

class EStmt : public EBase
{
public:
    virtual string to_string();
    virtual int get_type();
};

class EValue : public EStmt
{
public:
    virtual string to_string();
    virtual int get_type();
};

class EVariable : public EValue
{
public:
    string name;
    bool is_temp;
    EVariable(string name, bool is_temp=true);
    virtual string to_string();
    virtual int get_type();
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
    virtual int get_type();
};

class ELeftVal : public EValue 
{
public: 
    bool is_array;
    EValue* name;
    EValue* index;
    ELeftVal(EValue* name, EValue* index=nullptr, bool is_array=false);
    virtual string to_string();
    virtual int get_type();
};

class EVarStmt : public EStmt
{
public:
    EValue* name;
    EVarStmt(EValue* name);
    virtual string to_string();
    virtual int get_type();
};

class EVarArrayStmt : public EVarStmt 
{
public:
    int size;
    EVarArrayStmt(EValue* name, int size);
    virtual string to_string();
    virtual int get_type();
};

class EAssignStmt : public EStmt
{
public:
    EValue* res;
    EValue* value;
    EAssignStmt(EValue* res, int value);
    EAssignStmt(EValue* res, EValue* value);
    virtual string to_string();
    virtual int get_type();
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
    virtual int get_type();
};

class EUnaryExpr : public EStmt 
{
public:
    EValue* res;
    int op;
    EValue* rhs;
    EUnaryExpr(EValue* res, int op, EValue* rhs);
    virtual string to_string();
    virtual int get_type();
};

class EParamStmt : public EStmt 
{
public:
    EValue* name;
    EParamStmt(EValue* name);
    virtual string to_string();
    virtual int get_type();
};

class EFuncCall : public EValue 
{
public:
    string func_name;
    EFuncCall(string func_name);
    virtual string to_string();
    virtual int get_type();
};

class EJumpLabel : public EStmt 
{
public:
    string label;
    EJumpLabel(string label);
    virtual string to_string();
    virtual int get_type();
};

class EUnconditionalJump : public EStmt 
{
public:
    string label;
    EUnconditionalJump(string label);
    virtual string to_string();
    virtual int get_type();
};

class EConditionalJump : public EStmt 
{
public:
    string label;
    EValue* cond_name;
    bool cond_value;
    EConditionalJump(string label, EValue* cond_name, bool cond_value);
    virtual string to_string();
    virtual int get_type();
};

class EReturnStmt : public EStmt
{
public:
    EValue* value;
    EReturnStmt(EValue* value=nullptr);
    virtual string to_string();
    virtual int get_type();
};

class EFuncDef : public EStmt 
{
public: 
    string func_name;
    int args_num;
    EFuncDef(string func_name, int args_num);
    virtual string to_string();
    virtual int get_type();
};

class EFuncEnd : public EStmt 
{
public:
    string func_name;
    EFuncEnd(string func_name);
    virtual string to_string();
    virtual int get_type();
};

