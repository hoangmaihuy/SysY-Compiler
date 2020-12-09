#include <iostream> 
#include "symtab.hpp"
#include "tree.hpp"
#include "sysy.tab.hpp"


SymbolInfo::SymbolInfo(EVariable* ee_var, vector<int> value, bool is_const, bool is_array, vector<int> shape) 
  : ee_var(ee_var), value(value), is_const(is_const), is_array(is_array), shape(shape) {}

Context::Context()
{
    glob_id = temp_id = jump_id = 0;
    create_scope();
    eeyore_lists.push_back(EeyoreList("__global__", 0));
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

void Context::create_scope()
{
    sym_tabs.push_back({});
}

void Context::end_scope()
{
    sym_tabs.pop_back();
}

void Context::insert_symbol(string name, SymbolInfo value)
{
    sym_tabs.back().insert({name, value});
}

SymbolInfo& Context::find_symbol(string name)
{
    for (int i = sym_tabs.size()-1; i >= 0; i--)
    {
        auto find = sym_tabs[i].find(name);
        if (find != sym_tabs[i].end())
            return find->second;
    }
    cerr << "No symbol: " << name << "\n";
}

bool Context::is_global()
{
    return sym_tabs.size() == 1; 
}

string Context::create_eeyore_temp_var()
{
    return "t" + to_string(temp_id++);
}

string Context::create_eeyore_glob_var()
{
    return "T" + to_string(glob_id++);
}

void Context::insert_var(string name, EVariable* ee_var, bool is_const)
{
    SymbolInfo symbol(ee_var, {0}, is_const, false);
    insert_symbol(name, symbol);
}

void Context::insert_array(string name, EVariable* ee_var, vector<int>& shape, bool is_const)
{
    SymbolInfo symbol(ee_var, {}, is_const, true, shape);
    insert_symbol(name, symbol);
}

void Context::assign_var(string name, int value)
{
    SymbolInfo& symbol = find_symbol(name);
    symbol.value[0] = value;
}

int Context::get_var(string name)
{
    auto symbol = find_symbol(name);
    return symbol.value[0];
}

void Context::assign_array_item(string name, int index, int value)
{
    auto symbol = find_symbol(name);
    symbol.value[index] = value;
}

void Context::assign_array(string name, vector<int>& value)
{
    SymbolInfo& symbol = find_symbol(name);
    symbol.value = value;
}

int Context::get_array_item(string name, int index)
{
    SymbolInfo& symbol = find_symbol(name);
    return symbol.value[index];
}

void Context::insert_func(string func_name, int return_type, int args_num, bool built_in)
{
    func_tabs.insert({func_name, return_type});
    if (!built_in)
        eeyore_lists.push_back(EeyoreList(func_name, args_num));
}

int Context::get_func_return_type(string name)
{
    auto find = func_tabs.find(name);
    if (find != func_tabs.end())
        return func_tabs.find(name)->second;
    else 
        cerr << "No func def";
}

string Context::create_jump()
{
    return "l" + to_string(jump_id++); 
}

void Context::create_loop(string begin_loop, string end_loop)
{
    loops.push_back(make_pair(begin_loop, end_loop));
}

void Context::end_loop()
{
    loops.pop_back();
}

pair<string, string> Context::get_current_loop()
{
    return loops.back();
}

EeyoreList::EeyoreList(string func_name, int args_num) : func_name(func_name), args_num(args_num) { }

void Context::insert_eeyore_decl(EStmt* decl)
{
    if (is_global())
        eeyore_lists[0].decls.push_back(decl);
    else 
        eeyore_lists.back().decls.push_back(decl);
}

void Context::insert_eeyore_stmt(EStmt* stmt, int indent)
{
    if (is_global())
    {
        eeyore_lists[0].stmt_indents.push_back(indent);
        eeyore_lists[0].stmts.push_back(stmt);
    }
    else 
    {
        eeyore_lists.back().stmt_indents.push_back(indent);
        eeyore_lists.back().stmts.push_back(stmt);
    }
} 

void Context::fix_eeyore()
{
    for (EeyoreList& eeyore_list : eeyore_lists)
    {
        string func_name = eeyore_list.func_name;
        int args_num = eeyore_list.args_num;


        if (func_name == "__global__")
            continue;
        

        if (func_name == "main")
        {
            vector<EStmt*> tmp_decls;
            for (auto decl : eeyore_lists[0].decls)
            {
                EVariable* name = (EVariable*)((EVarStmt*)decl)->name;
                if (name->is_temp)
                    eeyore_list.decls.push_back(decl);
                else 
                    tmp_decls.push_back(decl);
            }
            eeyore_lists[0].decls = tmp_decls;

            eeyore_list.stmts.insert(eeyore_list.stmts.begin(), eeyore_lists[0].stmts.begin(), eeyore_lists[0].stmts.end());
            eeyore_list.stmt_indents.insert(eeyore_list.stmt_indents.begin(), eeyore_lists[0].stmt_indents.begin(), eeyore_lists[0].stmt_indents.end());

            eeyore_lists[0].stmts.clear();
            eeyore_lists[0].stmt_indents.clear();
        }
    }
}

void Context::get_eeyore_list(vector<EStmt*>& ee_list)
{
    for (auto eeyore_list : eeyore_lists)
    {
        string func_name = eeyore_list.func_name;
        if (func_name != "__global__")
            ee_list.push_back(new EFuncDef(func_name, eeyore_list.args_num));

        for (auto decl : eeyore_list.decls)
            ee_list.push_back(decl);

        if (func_name == "__global__") continue;

        for (auto stmt : eeyore_list.stmts)
            ee_list.push_back(stmt);

        ee_list.push_back(new EFuncEnd(func_name));
    }
}