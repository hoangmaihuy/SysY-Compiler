#include <iostream> 
#include "symtab.hpp"
#include "tree.hpp"
#include "source.tab.hpp"


SymbolInfo::SymbolInfo(string ee_name, vector<int> value, bool is_const, bool is_array, vector<int> shape) : ee_name(ee_name), value(value), is_const(is_const), is_array(is_array), shape(shape)
{
}

Context::Context()
{
    glob_id = temp_id = 0;
    create_scope();
    insert_func("getint", INT);
    insert_func("putint", VOID);
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

void Context::insert_func(string name, int return_type)
{
    func_tabs.insert({name, return_type});
}

int Context::get_func_return_type(string name)
{
    auto find = func_tabs.find(name);
    if (find != func_tabs.end())
        return func_tabs.find(name)->second;
    else 
        cerr << "No func def";
}

