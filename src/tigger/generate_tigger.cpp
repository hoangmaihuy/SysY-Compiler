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

void TiggerFunc::generate_tigger_decl(ContextTigger& ctx, EStmt *eeyore_decl)
{
    int e_type = eeyore_decl->get_type();
    if (e_type == E_VAR_STMT)
    {
        auto stmt = (EVarStmt*)eeyore_decl;
        string e_name = stmt->name->to_string();
        auto* t_var = new TVariable(ctx.new_global_var(), false);
        ctx.insert_var(e_name, t_var);
        stmts.emplace_back(new TVarDecl(t_var));
    }
    else if (e_type == E_VAR_ARRAY_STMT)
    {
        auto stmt = (EVarArrayStmt*)eeyore_decl;
        string e_name = stmt->name->to_string();
        int size = stmt->size;
        auto* t_var = new TVariable(ctx.new_global_var(), true);
        ctx.insert_var(e_name, t_var);
        stmts.emplace_back(new TArrayDecl(t_var, size));
    }
}

void TiggerFunc::generate_tigger_stmt(ContextTigger &ctx, EStmt* eeyore_stmt)
{
    int e_type = eeyore_stmt->get_type();
}