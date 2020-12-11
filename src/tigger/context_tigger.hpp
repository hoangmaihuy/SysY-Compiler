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
    bool has_func_call;
    vector<string> func_call_params;
    vector<TStmt*> stmts;
    unordered_map<string, int> stack_map;
    RegisterAllocator register_allocator;
    unordered_map<string, pair<int, int>> live_interval;

    TiggerFunc(string func_name, int args_num);

    bool has_to_save_callee_register() const;
    void save_callee_register();
    void restore_callee_register();

    bool has_to_save_caller_register() const;
    void save_caller_register();
    void restore_caller_register(string except_reg="");
    void register_allocation(EeyoreFunc& eeyore_func);
    void new_stack_var(const string& name, int size=1);
    int get_stack_loc(const string& name);
    bool check_var_in_stack(const string& name);
    void generate_tigger_decl(ContextTigger&, EStmt* eeyore_decl);
    void generate_tigger_stmt(ContextTigger& ctx, EStmt* eeyore_stmt);
    void push_func_call_params(ContextTigger& ctx);
};

class ContextTigger {
public:
    int var_id;
    vector<TiggerFunc> tigger_funcs;
    unordered_map<string, string> global_var_map;
    set<string> array_names;

    ContextTigger();

    string new_global_var();
    bool is_global_var(const string& e_name);

    void insert_func(string func_name, int args_num);
    void insert_var(const string& ee_name, string t_name);
    void insert_array(const string& ee_name);
    bool is_array(const string& ee_name);
    string find_var(const string& ee_name);
    void generate_tigger_func(EeyoreFunc& eeyore_func);

    TiggerFunc& get_current_func();

    void print_tigger(ostream& out);
};

