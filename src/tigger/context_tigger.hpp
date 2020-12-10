#pragma once

#include "globals.hpp"
#include "tigger.hpp"
#include "context_eeyore.hpp"
#include "register_allocator.hpp"

class ContextTigger;

class TiggerFunc {
public:
    string func_name;
    int args_num;
    int stack_size;
    vector<TStmt*> stmts;
    unordered_map<string, int> stack_map;
    RegisterAllocator register_allocator;

    TiggerFunc(string func_name, int args_num);
    void register_allocation(EeyoreFunc& eeyore_func);
    void new_stack_var(const string& name, int size=1);
    bool check_var_in_stack(const string& name);
    void generate_tigger_decl(ContextTigger&, EStmt* eeyore_decl);
    void generate_tigger_stmt(ContextTigger& ctx, EStmt* eeyore_stmt);
};

class ContextTigger {
public:
    int var_id;
    vector<TiggerFunc> tigger_funcs;
    unordered_map<string, TVariable*> symtab;

    ContextTigger();

    string new_global_var();

    void insert_func(string func_name, int args_num);
    void insert_var(const string& ee_name, TVariable* t_var);
    void insert_decl(TStmt* decl);
    void insert_stmt(TStmt* stmt);
    void generate_tigger_func(EeyoreFunc& eeyore_func);

    TiggerFunc& get_current_func();
};

