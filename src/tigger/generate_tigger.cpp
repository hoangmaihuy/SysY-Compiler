#include "context_tigger.hpp"
#include "context_eeyore.hpp"
#include "eeyore.hpp"
#include "tigger.hpp"
#include "sysy_tree.hpp"
#include "sysy.tab.hpp"
#include "util.hpp"


void ContextTigger::generate_tigger_func(EeyoreFunc& eeyore_func)
{
    string func_name = eeyore_func.func_name;
    int args_num = eeyore_func.args_num;
    insert_func(func_name, args_num);
    auto& tigger_func = get_current_func();

    for (auto decl : eeyore_func.decls)
    {
        if (decl->get_type() == E_VAR_ARRAY_STMT)
        {
            string ee_name = ((EVarArrayStmt*)decl)->name->to_string();
            insert_array(ee_name);
        }
    }

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
        {
            auto* func_def = new TFuncDef(func_name, args_num, stack_size);
            out << "\n" << func_def->to_string() << "\n";
        }
        for (auto stmt : tigger_func.stmts)
            out << "  " << stmt->to_string() << "\n";
        if (tigger_func.func_name == GLOB_NAME) continue;
        auto* func_end = new TFuncEnd(func_name);
        out << func_end->to_string() << "\n";
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

void ContextTigger::insert_array(const string &ee_name)
{
    array_names.insert(ee_name);
}

bool ContextTigger::is_array(const string &ee_name)
{
    return array_names.find(ee_name) != array_names.end();
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
    stmts.emplace_back(new TComment(eeyore_stmt->to_string()));
    if (e_type == E_RETURN)
    {
        auto* e_stmt = (EReturnStmt*)eeyore_stmt;
        if (e_stmt->value)
        {
            int value_type = e_stmt->value->get_type();
            if (value_type == E_NUMBER)
            {
                stmts.emplace_back(new TAssignNumber(RETURN_REG, ((ENumber*)e_stmt->value)->to_int()));
            }
            else if (value_type == E_VARIABLE)
            {
                string value_name = e_stmt->value->to_string();
                string value_reg = register_allocator.get_variable_register(ctx, *this, value_name);
                register_allocator.load_variable(ctx, *this, value_name, value_reg);
                stmts.emplace_back(new TCopyReg(RETURN_REG, value_reg));
            }
        }
        restore_callee_register();
        stmts.emplace_back(new TReturn());
    }
    else if (e_type == E_ASSIGN_STMT)
    {
        auto* e_stmt = (EAssignStmt*)eeyore_stmt;
        int res_type = e_stmt->res->get_type();
        int value_type = e_stmt->value->get_type();
        if (res_type == E_VARIABLE)
        {
            string res_name = e_stmt->res->to_string();
            string res_reg;
            if (value_type == E_VARIABLE) // x = y
            {
                string value_name = e_stmt->value->to_string();
                string value_reg = register_allocator.get_variable_register(ctx, *this, value_name);
                register_allocator.load_variable(ctx, *this, value_name, value_reg);
                res_reg = register_allocator.get_variable_register(ctx, *this, res_name);
                stmts.emplace_back(new TCopyReg(res_reg, value_reg));
                register_allocator.store_register(ctx, *this, res_reg, res_name);
            }
            else if (value_type == E_ARRAY_ITEM) // x = a[i]
            {
                auto* array_item = (EArrayItem*)e_stmt->value;
                string array_name = array_item->name->to_string();
                string array_index = array_item->index->to_string();
                int index_type = array_item->index->get_type();


                // global array
                if (ctx.is_global_var(array_name) || is_param(array_name))
                {
                    string array_reg = register_allocator.get_variable_register(ctx, *this, array_name);
                    if (!is_param(array_name))
                        register_allocator.load_variable(ctx, *this, array_name, array_reg);
                    res_reg = register_allocator.get_variable_register(ctx, *this, res_name);

                    if (index_type == E_NUMBER)
                    {
                        int index = ((ENumber*)array_item->index)->value;
                        stmts.emplace_back(new TArrayRead(res_reg, array_reg, index));
                    }
                    else if (index_type == E_VARIABLE)
                    {
                        string index_name = array_item->index->to_string();
                        string index_reg = register_allocator.get_variable_register(ctx, *this, index_name);
                        register_allocator.load_variable(ctx, *this, index_name, index_reg);
                        stmts.emplace_back(new TAssignRegOpReg(ADDRESS_REG, array_reg, PLUS, index_reg));
                        stmts.emplace_back(new TArrayRead(res_reg, ADDRESS_REG, 0));
                    }
                    register_allocator.store_register(ctx, *this, res_reg, res_name);
                }
                else // stack array
                {
                    res_reg = register_allocator.get_variable_register(ctx, *this, res_name);
                    int array_loc = get_stack_loc(array_name);
                    if (index_type == E_NUMBER)
                    {
                        int index = ((ENumber*)array_item->index)->value;
                        stmts.emplace_back(new TLoadStack(array_loc + index / 4, res_reg));
                    }
                    else if (index_type == E_VARIABLE)
                    {
                        string index_name = array_item->index->to_string();
                        string index_reg = register_allocator.get_variable_register(ctx, *this, index_name);
                        register_allocator.load_variable(ctx, *this, index_name, index_reg);
                        stmts.emplace_back(new TLoadaddrStack(array_loc, ADDRESS_REG));
                        stmts.emplace_back(new TAssignRegOpReg(ADDRESS_REG, ADDRESS_REG, PLUS, index_reg));
                        stmts.emplace_back(new TArrayRead(res_reg, ADDRESS_REG, 0));
                    }
                    register_allocator.store_register(ctx, *this, res_reg, res_name);
                }
            }
            else if (value_type == E_NUMBER) // x = const
            {
                res_reg = register_allocator.get_variable_register(ctx, *this, res_name);
                int value = ((ENumber*)e_stmt->value)->value;
                stmts.emplace_back(new TAssignNumber(res_reg, value));
                register_allocator.store_register(ctx, *this, res_reg, res_name);
            }
            else if (value_type == E_FUNC_CALL)
            {
                auto* func_call = (EFuncCall*)e_stmt->value;
                save_caller_register();
                push_func_call_params(ctx);
                stmts.emplace_back(new TFuncCall(func_call->func_name));
                restore_caller_register(RETURN_REG);
                res_reg = register_allocator.get_variable_register(ctx, *this, res_name);
                stmts.emplace_back(new TCopyReg(res_reg, RETURN_REG));
                int stack_loc = get_stack_loc(CALLER_SAVE_NAME + RETURN_REG);
                stmts.emplace_back(new TLoadStack(stack_loc, RETURN_REG));
            }
            register_allocator.map_reg_var(res_reg, res_name);
        }
        else if (res_type == E_ARRAY_ITEM)
        {
            auto* array_item = (EArrayItem*)e_stmt->res;
            string array_name = array_item->name->to_string();
            int index_type = array_item->index->get_type();
            string array_reg, value_reg;

            if (value_type == E_NUMBER)
            {
                stmts.emplace_back(new TAssignNumber(CONST_REG, ((ENumber*)e_stmt->value)->value));
                value_reg = CONST_REG;
            }
            else if (value_type == E_VARIABLE)
            {
                string value_name = e_stmt->value->to_string();
                value_reg = register_allocator.get_variable_register(ctx, *this, value_name);
                register_allocator.load_variable(ctx, *this, value_name, value_reg);
            }

            if (index_type == E_NUMBER)
            {
                int index = ((ENumber*)array_item->index)->value;
                if (ctx.is_global_var(array_name) || is_param(array_name))
                {
                    array_reg = register_allocator.get_variable_register(ctx, *this, array_name);
                    register_allocator.load_variable(ctx, *this, array_name, array_reg);
                    stmts.emplace_back(new TArrayWrite(array_reg, index, value_reg));
                }
                else
                {
                    int stack_loc = get_stack_loc(array_name);
                    stmts.emplace_back(new TStoreStack(value_reg, stack_loc + index / 4));
                }
            }
            else if (index_type == E_VARIABLE)
            {
                string index_name = array_item->index->to_string();
                string index_reg = register_allocator.get_variable_register(ctx, *this, index_name);
                register_allocator.load_variable(ctx, *this, index_name, index_reg);

                if (ctx.is_global_var(array_name) || is_param(array_name))
                {
                    array_reg = register_allocator.get_variable_register(ctx, *this, array_name);
                    register_allocator.load_variable(ctx, *this, array_name, array_reg);
                    stmts.emplace_back(new TAssignRegOpReg(ADDRESS_REG, array_reg, PLUS, index_reg));
                    stmts.emplace_back(new TArrayWrite(ADDRESS_REG, 0, value_reg));
                }
                else
                {
                    int stack_loc = get_stack_loc(array_name);
                    stmts.emplace_back(new TLoadaddrStack(stack_loc, ADDRESS_REG));
                    stmts.emplace_back(new TAssignRegOpReg(ADDRESS_REG, ADDRESS_REG, PLUS, index_reg));
                    stmts.emplace_back(new TArrayWrite(ADDRESS_REG, 0, value_reg));
                }
            }
        }
    }
    else if (e_type == E_BINARY_EXPR)
    {
        auto* e_stmt = (EBinaryExpr*)eeyore_stmt;
        string res_name = e_stmt->res->to_string();
        string lhs_name = e_stmt->lhs->to_string();
        string rhs_name = e_stmt->rhs->to_string();

        string lhs_reg = register_allocator.get_variable_register(ctx, *this, lhs_name);
        register_allocator.load_variable(ctx, *this, lhs_name, lhs_reg);
        string rhs_reg = register_allocator.get_variable_register(ctx, *this, rhs_name, lhs_reg);
        register_allocator.load_variable(ctx, *this, rhs_name, rhs_reg);
        string res_reg = register_allocator.get_variable_register(ctx, *this, res_name);

        stmts.emplace_back(new TAssignRegOpReg(res_reg, lhs_reg, e_stmt->op, rhs_reg));
        register_allocator.map_reg_var(res_reg, res_name);
        register_allocator.store_register(ctx, *this, res_reg, res_name);
    }
    else if (e_type == E_FUNC_CALL)
    {
        auto* func_call = (EFuncCall*)eeyore_stmt;
        save_caller_register();
        push_func_call_params(ctx);
        stmts.emplace_back(new TFuncCall(func_call->func_name));
        restore_caller_register();
    }
    else if (e_type == E_PARAM)
    {
        auto* e_stmt = (EParamStmt*)eeyore_stmt;
        string value_name = e_stmt->name->to_string();
        func_call_params.push_back(value_name);
    }
    else if (e_type == E_LABEL)
    {
        register_allocator.free_all();
        auto* e_stmt = (EJumpLabel*)eeyore_stmt;
        stmts.emplace_back(new TLabel(e_stmt->label));
    }
    else if (e_type == E_UNCOND_JUMP)
    {
        auto* e_stmt = (EUnconditionalJump*)eeyore_stmt;
        stmts.emplace_back(new TUnconditionalJump(e_stmt->label));
        register_allocator.free_all();
    }
    else if (e_type == E_COND_JUMP)
    {
        auto* e_stmt = (EConditionalJump*)eeyore_stmt;
        string cond_name = e_stmt->cond_name->to_string();
        string cond_reg = register_allocator.get_variable_register(ctx, *this, cond_name);
        register_allocator.load_variable(ctx, *this, cond_name, cond_reg);
        int op = (e_stmt->cond_value ? NE : EQ);
        stmts.emplace_back(new TConditionalJump(cond_reg, op, ZERO_REG, e_stmt->label));
        register_allocator.free_all();
    }
    else if (e_type == E_UNARY_EXPR)
    {
        auto* e_stmt = (EUnaryExpr*)eeyore_stmt;
        string res_name = e_stmt->res->to_string();
        string rhs_name = e_stmt->rhs->to_string();
        string rhs_reg = register_allocator.get_variable_register(ctx, *this, rhs_name);
        register_allocator.load_variable(ctx, *this, rhs_name, rhs_reg);
        string res_reg = register_allocator.get_variable_register(ctx, *this, res_name);
        stmts.emplace_back(new TAssignOpReg(res_reg, e_stmt->op, rhs_reg));
        register_allocator.map_reg_var(res_reg, res_name);
        register_allocator.store_register(ctx, *this, res_reg, res_name);
    }
}