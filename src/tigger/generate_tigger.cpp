#include "context_tigger.hpp"
#include "context_eeyore.hpp"
#include "eeyore.hpp"
#include "tigger.hpp"


void ContextTigger::generate_tigger_func(EeyoreFunc& eeyore_func)
{
    string func_name = eeyore_func.func_name;
    int args_num = eeyore_func.args_num;
    insert_func(func_name, args_num);
    auto& tigger_func = get_current_func();
    if (func_name == GLOB_NAME)
    {
        for (auto decl : eeyore_func.decls)
            tigger_func.generate_tigger_decl(*this, decl);
    }
    else
    {
        eeyore_func.liveness_analysis();
        tigger_func.has_func_call = eeyore_func.has_func_call;

        // allocate stack for caller save registers
        if (tigger_func.has_to_save_caller_register())
        {
            for (const auto& reg_name : RegisterAllocator::CALLER_SAVE_REG)
                tigger_func.new_stack_var(CALLER_SAVE_NAME + reg_name);
        }

        tigger_func.register_allocation(eeyore_func);
        tigger_func.save_callee_register();
        for (auto stmt : eeyore_func.stmts)
        {
            tigger_func.generate_tigger_stmt(*this, stmt);
        }
        tigger_func.restore_callee_register();
    }
}

void ContextTigger::print_tigger(ostream &out)
{
    for (auto& tigger_func : tigger_funcs)
    {
        string func_name = tigger_func.func_name;
        int args_num = tigger_func.args_num;
        int stack_size = tigger_func.stack_size;

        if (tigger_func.func_name != GLOB_NAME)
            out << "\nf_" << func_name << " [ " << args_num << " ] [ " << stack_size << " ]\n";
        for (auto stmt : tigger_func.stmts)
            out << "  " << stmt->to_string() << "\n";
        if (tigger_func.func_name == GLOB_NAME) continue;
        out << "end f_" << func_name << "\n";
    }
}

string ContextTigger::find_var(const string &ee_name)
{
    return global_var_map[ee_name];
}

bool ContextTigger::is_global_var(const string& ee_name)
{
    return (global_var_map.find(ee_name) != global_var_map.end());
}

void TiggerFunc::generate_tigger_decl(ContextTigger& ctx, EStmt *eeyore_decl)
{
    int e_type = eeyore_decl->get_type();
    if (e_type == E_VAR_STMT)
    {
        auto stmt = (EVarStmt*)eeyore_decl;
        string e_name = stmt->name->to_string();
        string t_name = ctx.new_global_var();
        ctx.insert_var(e_name, t_name);
        stmts.emplace_back(new TVarDecl(t_name));
    }
    else if (e_type == E_VAR_ARRAY_STMT)
    {
        auto stmt = (EVarArrayStmt*)eeyore_decl;
        string e_name = stmt->name->to_string();
        int size = stmt->size;
        string t_name = ctx.new_global_var();
        ctx.insert_var(e_name, t_name);
        stmts.emplace_back(new TArrayDecl(t_name, size));
    }
}

void TiggerFunc::generate_tigger_stmt(ContextTigger &ctx, EStmt* eeyore_stmt)
{
    int e_type = eeyore_stmt->get_type();
    if (e_type == E_RETURN)
    {
        auto* e_stmt = (EReturnStmt*)eeyore_stmt;
        if (e_stmt->value)
        {
            if (e_stmt->value->get_type() == E_NUMBER)
                stmts.emplace_back(new TAssignNumber(RETURN_REG, ((ENumber*)e_stmt->value)->to_int()));
        }
        stmts.emplace_back(new TReturn());
    }
    else if (e_type == E_ASSIGN_STMT)
    {
        auto* e_stmt = (EAssignStmt*)eeyore_stmt;
        int res_type = e_stmt->res->get_type();
        int value_type = e_stmt->res->get_type();
        if (res_type == E_VARIABLE)
        {
            string res_reg = register_allocator.get_register(stmts, e_stmt->res);
            if (value_type == E_VARIABLE) // x = y
            {
                string value_reg = register_allocator.get_register(stmts, e_stmt->value);
                stmts.emplace_back(new TCopyReg(res_reg, value_reg));
            }
            else if (value_type == E_ARRAY_ITEM) // x = a[i]
            {

            }
            else if (value_type == E_NUMBER) // x = const
            {

            }
        }
        else if (res_type == E_ARRAY_ITEM)
        {
            if (value_type == E_NUMBER) // a[i] = const
            {

            }
            else if (value_type == E_VARIABLE) // a[i] = x
            {

            }
        }
    }
    else if (e_type == E_BINARY_EXPR)
    {
        auto* e_stmt = (EBinaryExpr*)eeyore_stmt;
        string res_reg = register_allocator.get_register(stmts, e_stmt->res);
        string lhs_reg = register_allocator.get_register(stmts, e_stmt->lhs);
        string rhs_reg = register_allocator.get_register(stmts, e_stmt->rhs);
        stmts.emplace_back(new TAssignRegOpReg(res_reg, lhs_reg, e_stmt->op, rhs_reg));
        write_back(ctx, e_stmt->res, res_reg);
    }
}