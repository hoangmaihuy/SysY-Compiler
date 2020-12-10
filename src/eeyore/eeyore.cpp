#include "eeyore.hpp"

#include <utility>
#include "util/util.hpp"

string EStmt::to_string()
{
    return "EStmt";
}

int EStmt::get_type() { return E_STMT; }

string EValue::to_string()
{
    return "EValue";
}

int EValue::get_type() { return E_VALUE; }

vector<string> EValue::get_use_vars(bool is_lhs)
{
    return vector<string>();
}

vector<string> EValue::get_def_vars(bool is_lhs)
{
    return vector<string>();
}

EVariable::EVariable(string name, bool is_temp) : name(std::move(name)), is_temp(is_temp) {}

string EVariable::to_string()
{
    return name;
}

int EVariable::get_type() { return E_VARIABLE; }

vector<string> EVariable::get_use_vars(bool is_lhs)
{
    vector<string> use_vars = {name};
    return use_vars;
}

vector<string> EVariable::get_def_vars(bool is_lhs)
{
    vector<string> def_vars = {name};
    return def_vars;
}

ENumber::ENumber(int value) : value(value) {}

string ENumber::to_string()
{
    return std::to_string(value);
}

int ENumber::get_type() { return E_NUMBER; }

int ENumber::to_int()
{
    return value;
}

EArrayItem::EArrayItem(EValue* name, EValue* index) : name(name), index(index) {}

string EArrayItem::to_string()
{
    return name->to_string() + " [ " + index->to_string() + " ]";
}

int EArrayItem::get_type() { return E_ARRAY_ITEM; }

vector<string> EArrayItem::get_use_vars(bool is_lhs)
{
    vector<string> use_vars = {name->to_string(), index->to_string()};
    return use_vars;
}

EVarStmt::EVarStmt(EValue* name) : name(name) {}

string EVarStmt::to_string()
{
    return "var " + name->to_string();
}

int EVarStmt::get_type() { return E_VAR_STMT; }

EVarArrayStmt::EVarArrayStmt(EValue* name, int size) : EVarStmt(name), size(size) {}

string EVarArrayStmt::to_string()
{
    return "var " + std::to_string(size) + " " + EVarStmt::name->to_string();
}

int EVarArrayStmt::get_type() { return E_VAR_ARRAY_STMT; }

EAssignStmt::EAssignStmt(EValue* res, EValue* value) : res(res), value(value) {}

EAssignStmt::EAssignStmt(EValue* res, int value) : res(res)
{
    this->value = new ENumber(value);
}

string EAssignStmt::to_string()
{
    return res->to_string() + " = " + value->to_string();
}

int EAssignStmt::get_type() { return E_ASSIGN_STMT; }

EBinaryExpr::EBinaryExpr(EValue* res, EValue* lhs, int op, EValue* rhs) : res(res), lhs(lhs), op(op), rhs(rhs) {}

string EBinaryExpr::to_string()
{
    return res->to_string() + " = " + lhs->to_string() 
           + " " + get_token_str(op) + " " + rhs->to_string();
}

int EBinaryExpr::get_type() { return E_BINARY_EXPR; }

EUnaryExpr::EUnaryExpr(EValue* res, int op, EValue* rhs) : res(res), op(op), rhs(rhs) {}

string EUnaryExpr::to_string()
{
    return res->to_string() + " = " + get_token_str(op) + rhs->to_string();
}

int EUnaryExpr::get_type() { return E_UNARY_EXPR; }

EParamStmt::EParamStmt(EValue* name) : name(name) {}

string EParamStmt::to_string()
{
    return "param " + name->to_string();
}

int EParamStmt::get_type() { return E_PARAM; }

EFuncCall::EFuncCall(string func_name) : func_name(std::move(func_name)) {}

string EFuncCall::to_string()
{
    return "call f_" + func_name;
}

int EFuncCall::get_type() { return E_FUNC_CALL; }

EJumpLabel::EJumpLabel(string label) : label(std::move(label)) {}

string EJumpLabel::to_string()
{
    return label + ":";
}

int EJumpLabel::get_type() { return E_LABEL; }

EUnconditionalJump::EUnconditionalJump(string label) : label(std::move(label)) {}

string EUnconditionalJump::to_string()
{
    return "goto " + label;
}

int EUnconditionalJump::get_type() { return E_UNCOND_JUMP; }

EConditionalJump::EConditionalJump(string label, EValue* cond_name, bool cond_value) : label(std::move(label)), cond_name(cond_name), cond_value(cond_value) {}

string EConditionalJump::to_string()
{
    return "if " + cond_name->to_string() + (cond_value ? " != 0" : " == 0") + " goto " + label;
}

int EConditionalJump::get_type() { return E_COND_JUMP; }

EReturnStmt::EReturnStmt(EValue* value) : value(value) {}

string EReturnStmt::to_string()
{
    if (value)
        return "return " + value->to_string();
    else 
        return "return";
}

int EReturnStmt::get_type() { return E_RETURN; }

EFuncDef::EFuncDef(string func_name, int args_num) : func_name(std::move(func_name)), args_num(args_num) {}

string EFuncDef::to_string()
{
    return "f_" + func_name + " [ " + std::to_string(args_num) + " ]";
}

int EFuncDef::get_type() { return E_FUNC_DEF; }

EFuncEnd::EFuncEnd(string func_name) : func_name(std::move(func_name)) {}

string EFuncEnd::to_string()
{
    return "end f_" + func_name;
}

int EFuncEnd::get_type() { return E_FUNC_END; }