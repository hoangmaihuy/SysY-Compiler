#include <iostream> 
#include "symtab.hpp"
#include "tree.hpp"
#include "source.tab.hpp"


SymbolInfo::SymbolInfo(string ee_name, vector<int> value, bool is_const, bool is_array, vector<int> shape) : ee_name(ee_name), value(value), is_const(is_const), is_array(is_array), shape(shape)
{
}

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
}

void Context::create_scope()
{
    sym_tabs.push_back({});
}

void Context::end_scope()
{
    sym_tabs.pop_back();
}

string Context::insert_symbol(string name, SymbolInfo value)
{
    sym_tabs.back().insert({name, value});
    return value.ee_name;
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

void Context::insert_var(string name, string ee_name, bool is_const)
{
    SymbolInfo symbol(ee_name, {0}, is_const, false);
    insert_symbol(name, symbol);
}

void Context::insert_array(string name, string ee_name, vector<int>& shape, bool is_const)
{
    SymbolInfo symbol(ee_name, {}, is_const, true, shape);
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

void Context::insert_eeyore_decl(string decl)
{
    if (is_global())
        eeyore_lists[0].decls.push_back(decl);
    else 
        eeyore_lists.back().decls.push_back(decl);
}

void Context::insert_eeyore_stmt(string stmt, int indent)
{
    for (int i = 0; i < indent; i++) stmt = "  " + stmt;
    if (is_global())
        eeyore_lists[0].stmts.push_back(stmt);
    else 
        eeyore_lists.back().stmts.push_back(stmt);
} 

void Context::print_eeyore(ostream& out)
{
    for (auto eeyore_list : eeyore_lists)
    {
        string func_name = eeyore_list.func_name;
        int args_num = eeyore_list.args_num;
        if (func_name == "__global__")
        {
            for (auto decl : eeyore_list.decls) 
                out << decl << "\n";
            continue;
        } 

        out << "f_" + func_name + " [" + to_string(args_num) + "]" << "\n";
        if (func_name == "main")
        {
            for (auto stmt : eeyore_lists[0].stmts)
                out << "  " << stmt << "\n";
        }
        for (auto decl : eeyore_list.decls)
            out << "  " << decl << "\n";
        for (auto stmt : eeyore_list.stmts)
            out << stmt << "\n";
        out << "end f_" + func_name << "\n";
    }
}