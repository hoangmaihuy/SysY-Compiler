#include "globals.hpp"
#include "context_eeyore.hpp"
#include "sysy_tree.hpp"
#include "sysy.tab.hpp"
#include "util/util.hpp"


SymbolInfo::SymbolInfo(EVariable* ee_var, vector<int> value, bool is_const, bool is_array, vector<int> shape) 
  : ee_var(ee_var), value(std::move(value)), is_const(is_const), is_array(is_array), shape(std::move(shape)) {}

ContextEeyore::ContextEeyore()
{
    glob_id = temp_id = jump_id = 0;
    create_scope();
    eeyore_funcs.emplace_back("__global__", 0);
    insert_func("getint", INT, 0, true);
    insert_func("getch", INT, 0, true);
    insert_func("getarray", INT, 1, true);
    insert_func("putint", VOID, 1, true);
    insert_func("putch", VOID, 1, true);
    insert_func("putarray", VOID, 2, true);
    insert_func("starttime", VOID, 0, true);
    insert_func("stoptime", VOID, 0, true);
    insert_func("_sysy_starttime", VOID, 1, true);
    insert_func("_sysy_stoptime", VOID, 0, true);
}

void ContextEeyore::create_scope()
{
    sym_tabs.emplace_back();
}

void ContextEeyore::end_scope()
{
    sym_tabs.pop_back();
}

void ContextEeyore::insert_symbol(const string& name, SymbolInfo value)
{
    sym_tabs.back().insert({name, value});
}

SymbolInfo& ContextEeyore::find_symbol(const string& name)
{
    for (int i = sym_tabs.size()-1; i >= 0; i--)
    {
        auto find = sym_tabs[i].find(name);
        if (find != sym_tabs[i].end())
            return find->second;
    }
    cerr << "No symbol: " << name << "\n";
}

bool ContextEeyore::is_global() const
{
    return sym_tabs.size() == 1; 
}

string ContextEeyore::create_eeyore_temp_var()
{
    return "t" + to_string(temp_id++);
}

string ContextEeyore::create_eeyore_glob_var()
{
    return "T" + to_string(glob_id++);
}

void ContextEeyore::insert_var(string name, EVariable* ee_var, bool is_const)
{
    SymbolInfo symbol(ee_var, {0}, is_const, false);
    insert_symbol(name, symbol);
}

void ContextEeyore::insert_array(string name, EVariable* ee_var, vector<int>& shape, bool is_const)
{
    SymbolInfo symbol(ee_var, {}, is_const, true, shape);
    insert_symbol(name, symbol);
}

void ContextEeyore::assign_var(string name, int value)
{
    SymbolInfo& symbol = find_symbol(name);
    symbol.value[0] = value;
}

int ContextEeyore::get_var(string name)
{
    auto symbol = find_symbol(name);
    return symbol.value[0];
}

void ContextEeyore::assign_array_item(string name, int index, int value)
{
    auto symbol = find_symbol(name);
    symbol.value[index] = value;
}

void ContextEeyore::assign_array(string name, vector<int>& value)
{
    SymbolInfo& symbol = find_symbol(name);
    symbol.value = value;
}

int ContextEeyore::get_array_item(string name, int index)
{
    SymbolInfo& symbol = find_symbol(name);
    return symbol.value[index];
}

void ContextEeyore::insert_func(const string& func_name, int return_type, int args_num, bool built_in)
{
    func_tabs.insert({func_name, return_type});
    if (!built_in)
        eeyore_funcs.emplace_back(func_name, args_num);
}

int ContextEeyore::get_func_return_type(const string& name)
{
    auto find = func_tabs.find(name);
    if (find != func_tabs.end())
        return func_tabs.find(name)->second;
    else 
        cerr << "No func def";
    return 0;
}

string ContextEeyore::create_jump()
{
    return "l" + to_string(jump_id++); 
}

void ContextEeyore::create_loop(const string& begin_loop, const string& end_loop)
{
    loops.emplace_back(begin_loop, end_loop);
}

void ContextEeyore::end_loop()
{
    loops.pop_back();
}

pair<string, string> ContextEeyore::get_current_loop()
{
    return loops.back();
}

EeyoreFunc::EeyoreFunc(string func_name, int args_num) : func_name(std::move(func_name)), args_num(args_num)
{
    has_func_call = false;
}

void EeyoreFunc::liveness_analysis()
{
    // TODO: fix this with data-flow analysis
    set<string> var_names;

    EAssignStmt* assign_stmt;
    EBinaryExpr* binary_expr;
    EUnaryExpr* unary_expr;
    EReturnStmt* return_stmt;
    EParamStmt* param_stmt;
    EConditionalJump* cond_jump;

    // compute first_def
    for (int i = 0; i < stmts.size(); i++)
    {
        def_vars.emplace_back();
        switch (stmts[i]->get_type())
        {
            case E_ASSIGN_STMT:
                assign_stmt = (EAssignStmt*)stmts[i];
                concat_string_vector(def_vars.back(), assign_stmt->res->get_def_vars(true));
                if (assign_stmt->value->get_type() == E_FUNC_CALL)
                    has_func_call = true;
                break;
            case E_BINARY_EXPR:
                binary_expr = (EBinaryExpr*)stmts[i];
                concat_string_vector(def_vars.back(), binary_expr->res->get_def_vars(true));
                break;
            case E_UNARY_EXPR:
                unary_expr = (EUnaryExpr*)stmts[i];
                concat_string_vector(def_vars.back(), unary_expr->res->get_def_vars(true));
                break;
            case E_FUNC_CALL:
                has_func_call = true;
                break;
            default:
                break;
        }

        for (const auto& var_name : def_vars.back())
        {
            var_names.insert(var_name);
            if (first_def.find(var_name) != first_def.end())
                first_def.insert({var_name, i});
        }
    }

    // compute last_use
    for (int i = (int)stmts.size()-1; i >= 0; i--)
    {
        use_vars.emplace_back();
        auto stmt = stmts[i];
        switch (stmt->get_type())
        {
            case E_ASSIGN_STMT:
                assign_stmt = (EAssignStmt*)stmts[i];
                concat_string_vector(use_vars.back(), assign_stmt->res->get_use_vars(true));
                concat_string_vector(use_vars.back(), assign_stmt->value->get_use_vars(false));
                break;
            case E_BINARY_EXPR:
                binary_expr = (EBinaryExpr*)stmts[i];
                concat_string_vector(use_vars.back(), binary_expr->lhs->get_use_vars(false));
                concat_string_vector(use_vars.back(), binary_expr->rhs->get_use_vars(false));
                break;
            case E_UNARY_EXPR:
                unary_expr = (EUnaryExpr*)stmts[i];
                concat_string_vector(use_vars.back(), unary_expr->rhs->get_use_vars(false));
                break;
            case E_RETURN:
                return_stmt = (EReturnStmt*)stmts[i];
                concat_string_vector(use_vars.back(), return_stmt->value->get_use_vars(false));
                break;
            case E_PARAM:
                param_stmt = (EParamStmt*)stmts[i];
                concat_string_vector(use_vars.back(), param_stmt->name->get_use_vars(false));
                break;
            case E_COND_JUMP:
                cond_jump = (EConditionalJump*)stmts[i];
                concat_string_vector(use_vars.back(), cond_jump->cond_name->get_use_vars(false));
            default:
                break;
        }

        for (const auto& var_name : use_vars.back())
        {
            var_names.insert(var_name);
            if (last_use.find(var_name) != last_use.end())
                last_use.insert({var_name, i});
        }
    }

    // compute live intervals
    for (auto var_name : var_names)
    {
        if (var_name[0] != 'p') // not param
        {
            int _first_def = 0, _last_use = stmts.size();
            auto var_def = first_def.find(var_name);
            auto var_use = last_use.find(var_name);
            if (var_def != first_def.end())
                _first_def = var_def->second;
            if (var_use != last_use.end())
                _last_use = var_use->second;
            live_intervals.emplace_back(LiveInterval(var_name, _first_def, _last_use));
        }
    }
    sort(live_intervals.begin(), live_intervals.end());
}

void ContextEeyore::insert_decl(EStmt* decl)
{
    if (is_global())
        eeyore_funcs[0].decls.push_back(decl);
    else 
        eeyore_funcs.back().decls.push_back(decl);
}

void ContextEeyore::insert_stmt(EStmt* stmt, int indent)
{
    if (is_global())
    {
        eeyore_funcs[0].stmt_indents.push_back(indent);
        eeyore_funcs[0].stmts.push_back(stmt);
    }
    else 
    {
        eeyore_funcs.back().stmt_indents.push_back(indent);
        eeyore_funcs.back().stmts.push_back(stmt);
    }
} 

void ContextEeyore::fix_eeyore()
{
    for (EeyoreFunc& eeyore_func : eeyore_funcs)
    {
        string func_name = eeyore_func.func_name;
        int args_num = eeyore_func.args_num;


        if (func_name == GLOB_NAME)
            continue;
        

        if (func_name == "main")
        {
            vector<EStmt*> tmp_decls;
            for (auto decl : eeyore_funcs[0].decls)
            {
                auto* name = (EVariable*)((EVarStmt*)decl)->name;
                if (name->is_temp)
                    eeyore_func.decls.push_back(decl);
                else 
                    tmp_decls.push_back(decl);
            }
            eeyore_funcs[0].decls = tmp_decls;

            eeyore_func.stmts.insert(eeyore_func.stmts.begin(), eeyore_funcs[0].stmts.begin(), eeyore_funcs[0].stmts.end());
            eeyore_func.stmt_indents.insert(eeyore_func.stmt_indents.begin(), eeyore_funcs[0].stmt_indents.begin(), eeyore_funcs[0].stmt_indents.end());

            eeyore_funcs[0].stmts.clear();
            eeyore_funcs[0].stmt_indents.clear();
        }
    }
}

void ContextEeyore::print_eeyore(ostream& out)
{
    for (auto& eeyore_func : eeyore_funcs)
    {
        string func_name = eeyore_func.func_name;
        if (func_name != GLOB_NAME)
        {
            auto* func_def = new EFuncDef(func_name, eeyore_func.args_num);
            out << "\n";
            out << func_def->to_string() << "\n";
            delete func_def;
        }

        for (auto decl : eeyore_func.decls)
        {
            if (func_name != GLOB_NAME) out << "  ";
            out << decl->to_string() << "\n";
        }

        if (func_name == GLOB_NAME) continue;

        for (auto i = 0; i < eeyore_func.stmts.size(); i++)
        {
            for (int j = 0; j < eeyore_func.stmt_indents[i]; j++) out << " ";
            out << eeyore_func.stmts[i]->to_string() << "\n";
        }

        auto* func_end = new EFuncEnd(func_name);
        out << func_end->to_string() << "\n";
        delete func_end;
    }
}

LiveInterval::LiveInterval(string name, int tin, int tout) : name(std::move(name)), tin(tin), tout(tout) {}

bool LiveInterval::operator < (const LiveInterval &other) const
{
    if (tin != other.tin)
        return tin < other.tin;
    return tout < other.tout;
}
