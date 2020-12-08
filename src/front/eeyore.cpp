#include "eeyore.hpp"
#include "util.hpp"

string EBase::to_string()
{
    return "EBase";
}

string EStmt::to_string()
{
    return "EStmt";
}

string EValue::to_string()
{
    return "EValue";
}

EVariable::EVariable(string name, bool is_temp) : name(name), is_temp(is_temp) {}

string EVariable::to_string()
{
    return name;
}

ERightVal::ERightVal(EValue* name) : name(name)
{
    is_number = false;
}

ERightVal::ERightVal(int value) : value(value)
{
    is_number = true;
}

string ERightVal::to_string()
{
    if (is_number) return std::to_string(value);
    else 
    {
        return name->to_string();
    }
}

ELeftVal::ELeftVal(EValue* name, EValue* index, bool is_array) : name(name), index(index), is_array(is_array) {}

string ELeftVal::to_string()
{
    if (!is_array) return name->to_string();
    else 
    {
        return name->to_string() + " [ " + index->to_string() + " ]";
    }
}

EVarStmt::EVarStmt(EValue* name) : name(name) {}

string EVarStmt::to_string()
{
    return "var " + name->to_string();
}

EVarArrayStmt::EVarArrayStmt(EValue* name, int size) : EVarStmt(name), size(size) {}

string EVarArrayStmt::to_string()
{
    return "var " + std::to_string(size) + " " + EVarStmt::name->to_string();
}

EAssignStmt::EAssignStmt(EValue* res, EValue* value) : res(res), value(value) {}

EAssignStmt::EAssignStmt(EValue* res, int value) : res(res)
{
    this->value = new ERightVal(value);
}

string EAssignStmt::to_string()
{
    return res->to_string() + " = " + value->to_string();
}

EBinaryExpr::EBinaryExpr(EValue* res, EValue* lhs, int op, EValue* rhs) : res(res), lhs(lhs), op(op), rhs(rhs) {}

string EBinaryExpr::to_string()
{
    return res->to_string() + " = " + lhs->to_string() 
           + " " + get_token_str(op) + " " + rhs->to_string();
}

EUnaryExpr::EUnaryExpr(EValue* res, int op, EValue* rhs) : res(res), op(op), rhs(rhs) {}

string EUnaryExpr::to_string()
{
    return res->to_string() + " = " + get_token_str(op) + rhs->to_string();
}

EParamStmt::EParamStmt(EValue* name) : name(name) {}

string EParamStmt::to_string()
{
    return "param " + name->to_string();
}

EFuncCall::EFuncCall(string func_name) : func_name(func_name) {}

string EFuncCall::to_string()
{
    return "call f_" + func_name;
}

EJumpLabel::EJumpLabel(string label) : label(label) {}

string EJumpLabel::to_string()
{
    return label + ":";
}

EUnconditionalJump::EUnconditionalJump(string label) : label(label) {}

string EUnconditionalJump::to_string()
{
    return "goto " + label;
}

EConditionalJump::EConditionalJump(string label, EValue* cond_name, bool cond_value) : label(label), cond_name(cond_name), cond_value(cond_value) {}

string EConditionalJump::to_string()
{
    return "if " + cond_name->to_string() + (cond_value ? " != 0" : " == 0") + " goto " + label;
}

EReturnStmt::EReturnStmt(EValue* value) : value(value) {}

string EReturnStmt::to_string()
{
    if (value)
        return "return " + value->to_string();
    else 
        return "return";
}

EFuncDef::EFuncDef(string func_name, int args_num) : func_name(func_name), args_num(args_num) {}

string EFuncDef::to_string()
{
    return "f_" + func_name + " [ " + std::to_string(args_num) + " ]";
}

EFuncEnd::EFuncEnd(string func_name) : func_name(func_name) {}

string EFuncEnd::to_string()
{
    return "end f_" + func_name;
}