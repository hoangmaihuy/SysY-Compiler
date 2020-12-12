//
// Created by mew on 09/12/2020.
//

#include "tigger.hpp"
#include "util.hpp"

#include <utility>

TVarDecl::TVarDecl(string name, int value) : name(std::move(name)), value(value) {}

string TVarDecl::to_string()
{
    return name + " = " + std::to_string(value);
}


TArrayDecl::TArrayDecl(string name, int size) : name(std::move(name)), size(size) {}

string TArrayDecl::to_string()
{
    return name + " = malloc " + std::to_string(size);
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

TAssignNumber::TAssignNumber(string reg_name, int value) : reg_name(std::move(reg_name)), value(value)
{
}

string TAssignNumber::to_string()
{
    return reg_name + " = " + std::to_string(value);
}

TCopyReg::TCopyReg(string res_reg, string value_reg) : res_reg(std::move(res_reg)), value_reg(std::move(value_reg)) {}

string TCopyReg::to_string()
{
    return res_reg + " = " + value_reg;
}

TAssignRegOpReg::TAssignRegOpReg(string res_reg, string lhs_reg, int op, string rhs_reg) : res_reg(res_reg), lhs_reg(lhs_reg), op(op), rhs_reg(rhs_reg)
{
}

string TAssignRegOpReg::to_string()
{
    return res_reg + " = " + lhs_reg + " "  + get_token_str(op) + " " + rhs_reg;
}

TLoadaddrGlobal::TLoadaddrGlobal(string var_name, string reg_name) : var_name(var_name), reg_name(reg_name)
{
}

string TLoadaddrGlobal::to_string()
{
    return "loadaddr " + var_name + " " + reg_name;
}

TAssignOpReg::TAssignOpReg(string res_reg, int op, string rhs_reg) : res_reg(res_reg), op(op), rhs_reg(rhs_reg) {}

string TAssignOpReg::to_string()
{
    return res_reg + " = " + get_token_str(op) + " " + rhs_reg;
}

TArrayWrite::TArrayWrite(string array_reg, int index, string value_reg) : array_reg(array_reg), index(index), value_reg(value_reg) {}

string TArrayWrite::to_string()
{
    return array_reg + " [ " + std::to_string(index) + " ] = " + value_reg;
}

TArrayRead::TArrayRead(string res_reg, string array_reg, int index) : res_reg(res_reg), array_reg(array_reg), index(index) {}

string TArrayRead::to_string()
{
    return res_reg + " = " + array_reg + " [ " + std::to_string(index) + " ]";
}

TConditionalJump::TConditionalJump(const string &reg1, int op, const string &reg2, const string& label) : reg_1(reg1), op(op), reg_2(reg2), label(label) {}

string TConditionalJump::to_string()
{
    return "if " + reg_1 + " " + get_token_str(op) + " " + reg_2 + " goto " + label;
}

TUnconditionalJump::TUnconditionalJump(string label) : label(label) {}

string TUnconditionalJump::to_string()
{
    return "goto " + label;
}

TLabel::TLabel(string label) : label(label) {}

string TLabel::to_string()
{
    return label + ":";
}

TFuncCall::TFuncCall(string func_name) : func_name(func_name) {}

string TFuncCall::to_string()
{
    return "call f_" + func_name;
}

TLoadGlobal::TLoadGlobal(string var_name, string reg_name) : var_name(var_name), reg_name(reg_name) {}

string TLoadGlobal::to_string()
{
    return "load " + var_name + " " + reg_name;
}

TLoadaddrStack::TLoadaddrStack(int loc, string reg_name) : loc(loc), reg_name(reg_name) {}

string TLoadaddrStack::to_string()
{
    return "loadaddr " + std::to_string(loc) + " " + reg_name;
}

TComment::TComment(string comment) : comment(comment) {}

string TComment::to_string()
{
    return "// " + comment;
}


TFuncDef::TFuncDef(string func_name, int args_num, int stack_size) : func_name(func_name), args_num(args_num), stack_size(stack_size)
{
}

string TFuncDef::to_string()
{
    return "f_" + func_name + " [ " + std::to_string(args_num) + " ] [ " + std::to_string(stack_size) + " ]";
}

TFuncEnd::TFuncEnd(string func_name) : func_name(func_name)
{
}

string TFuncEnd::to_string()
{
    return "end f_" + func_name;
}
