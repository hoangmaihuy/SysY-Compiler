#include "tigger.hpp"
#include "sysy_tree.hpp"
#include "sysy.tab.hpp"

int stk;

void TStmt::generate_riscv(vector<string>& riscv_list)
{
}

void TVarDecl::generate_riscv(vector<string> &riscv_list)
{
    riscv_list.emplace_back("\t.global\t" + name);
    riscv_list.emplace_back("\t.section\t.sdata");
    riscv_list.emplace_back("\t.align\t2");
    riscv_list.emplace_back("\t.type\t" + name + ", @object");
    riscv_list.emplace_back("\t.size\t" + name + ", 4");
    riscv_list.emplace_back(name + ":");
    riscv_list.emplace_back("\t.word\t" + std::to_string(value));
}

void TArrayDecl::generate_riscv(vector<string> &riscv_list)
{
    riscv_list.emplace_back("\t.comm\t" + name + "," + std::to_string(size*4) + ",4");
}

void TAssignNumber::generate_riscv(vector<string> &riscv_list)
{
    riscv_list.emplace_back("\tli  \t" + reg_name + "," + std::to_string(value));
}

void TAssignRegOpReg::generate_riscv(vector<string> &riscv_list)
{
    if (op == PLUS)
        riscv_list.emplace_back("\tadd \t" + res_reg + "," + lhs_reg + "," + rhs_reg);
    else if (op == MINUS)
        riscv_list.emplace_back("\tsub \t" + res_reg + "," + lhs_reg + "," + rhs_reg);
    else if (op == DIV)
        riscv_list.emplace_back("\tdiv \t" + res_reg + "," + lhs_reg + "," + rhs_reg);
    else if (op == MUL)
        riscv_list.emplace_back("\tmul \t" + res_reg + "," + lhs_reg + "," + rhs_reg);
    else if (op == MOD)
        riscv_list.emplace_back("\trem \t" + res_reg + "," + lhs_reg + "," + rhs_reg);
    else if (op == AND)
    {
        riscv_list.emplace_back("\tseqz\t" + res_reg + "," + lhs_reg);
        riscv_list.emplace_back("\taddi\t" + res_reg + "," + res_reg + ",-1");
        riscv_list.emplace_back("\tand \t" + res_reg + "," + res_reg + "," + rhs_reg);
        riscv_list.emplace_back("\tsnez\t" + res_reg + "," + res_reg);
    }
    else if (op == OR)
    {
        riscv_list.emplace_back("\tor  \t" + res_reg + "," + lhs_reg + "," + rhs_reg);
        riscv_list.emplace_back("\tsnez\t" + res_reg + "," + res_reg);
    }
    else if (op == LT)
        riscv_list.emplace_back("\tslt \t" + res_reg + "," + lhs_reg + "," + rhs_reg);
    else if (op == GT)
        riscv_list.emplace_back("\tsgt \t" + res_reg + "," + lhs_reg + "," + rhs_reg);
    else if (op == LE)
    {
        riscv_list.emplace_back("\tsgt \t" + res_reg + "," + lhs_reg + "," + rhs_reg);
        riscv_list.emplace_back("\tseqz\t" + res_reg + "," + res_reg);
    }
    else if (op == GE)
    {
        riscv_list.emplace_back("\tslt \t" + res_reg + "," + lhs_reg + "," + rhs_reg);
        riscv_list.emplace_back("\tseqz\t" + res_reg + "," + res_reg);
    }
    else if (op == EQ)
    {
        riscv_list.emplace_back("\txor \t" + res_reg + "," + lhs_reg + "," + rhs_reg);
        riscv_list.emplace_back("\tseqz\t" + res_reg + "," + res_reg);
    }
    else if (op == NE)
    {
        riscv_list.emplace_back("\txor \t" + res_reg + "," + lhs_reg + "," + rhs_reg);
        riscv_list.emplace_back("\tsnez\t" + res_reg + "," + res_reg);
    }
}

void TAssignOpReg::generate_riscv(vector<string> &riscv_list)
{
    if (op == MINUS)
        riscv_list.emplace_back("\tsub \t" + res_reg + ",x0," + rhs_reg);
    else if (op == NOT)
    {
        riscv_list.emplace_back("\txori\t" + res_reg + "," + rhs_reg + ",-1");
        riscv_list.emplace_back("\tsnez\t" + res_reg + "," + res_reg);
    }

}

void TCopyReg::generate_riscv(vector<string> &riscv_list)
{
    riscv_list.emplace_back("\tmv  \t" + res_reg + "," + value_reg);
}

void TLabel::generate_riscv(vector<string> &riscv_list)
{
    riscv_list.emplace_back("." + label + ":");
}

void TConditionalJump::generate_riscv(vector<string> &riscv_list)
{
    if (op == LT)
        riscv_list.emplace_back("\tblt \t" + reg_1 + "," + reg_2 + ",." + label);
    else if (op == GT)
        riscv_list.emplace_back("\tbgt \t" + reg_1 + "," + reg_2 + ",." + label);
    else if (op == LE)
        riscv_list.emplace_back("\tble \t" + reg_1 + "," + reg_2 + ",." + label);
    else if (op == GE)
        riscv_list.emplace_back("\tble \t" + reg_2 + "," + reg_1 + ",." + label);
    else if (op == EQ)
        riscv_list.emplace_back("\tbeq \t" + reg_1 + "," + reg_2 + ",." + label);
    else if (op == NE)
        riscv_list.emplace_back("\tbne \t" + reg_1 + "," + reg_2 + ",." + label);
}

void TUnconditionalJump::generate_riscv(vector<string> &riscv_list)
{
    riscv_list.emplace_back("\tj   \t." + label);
}

void TFuncCall::generate_riscv(vector<string> &riscv_list)
{
    riscv_list.emplace_back("\tcall\t" + func_name);
}

void TFuncDef::generate_riscv(vector<string> &riscv_list)
{
    riscv_list.emplace_back("\t.text");
    riscv_list.emplace_back("\t.align\t2");
    riscv_list.emplace_back("\t.global\t" + func_name);
    riscv_list.emplace_back("\t.type\t" + func_name + ", @function");
    riscv_list.emplace_back(func_name + ":");
    stk = (stack_size / 4 + 1) * 16;
    riscv_list.emplace_back("\taddi \tsp,sp,-" + std::to_string(stk));
    riscv_list.emplace_back("\tsw  \tra," + std::to_string(stk-4) + "(sp)");
}

void TFuncEnd::generate_riscv(vector<string> &riscv_list)
{
    riscv_list.emplace_back("\t.size\t" + func_name + ", .-" + func_name);
}

void TStoreStack::generate_riscv(vector<string> &riscv_list)
{
    riscv_list.emplace_back("\tsw  \t" + reg_name + "," + std::to_string(loc * 4) + "(sp)");
}

void TLoadStack::generate_riscv(vector<string> &riscv_list)
{
    riscv_list.emplace_back("\tlw  \t" + reg_name + "," + std::to_string(loc * 4) + "(sp)");
}

void TLoadGlobal::generate_riscv(vector<string> &riscv_list)
{
    riscv_list.emplace_back("\tlui \t" + reg_name + ",%hi(" + var_name + ")");
    riscv_list.emplace_back("\tlw  \t" + reg_name + ",%lo(" + var_name + ")(" + reg_name + ")");
}

void TLoadaddrStack::generate_riscv(vector<string> &riscv_list)
{
    riscv_list.emplace_back("\taddi\t" + reg_name + ",sp," + std::to_string(loc * 4));
}

void TLoadaddrGlobal::generate_riscv(vector<string> &riscv_list)
{
    riscv_list.emplace_back("\tlui \t" + reg_name + ",%hi(" + var_name + ")");
    riscv_list.emplace_back("\tadd \t" + reg_name + "," + reg_name + ",%lo(" + var_name + ")");
}

void TReturn::generate_riscv(vector<string> &riscv_list)
{
    riscv_list.emplace_back("\tlw  \tra," + std::to_string(stk-4) + "(sp)");
    riscv_list.emplace_back("\taddi\tsp,sp," + std::to_string(stk));
    riscv_list.emplace_back("\tjr  \tra");
}

void TArrayWrite::generate_riscv(vector<string> &riscv_list)
{
    riscv_list.emplace_back("\tsw  \t" + value_reg + "," + std::to_string(index) + "(" + array_reg + ")");
}

void TArrayRead::generate_riscv(vector<string> &riscv_list)
{
    riscv_list.emplace_back("\tlw  \t" + res_reg + "," + std::to_string(index) + "(" + array_reg + ")");
}