#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "eeyore.hpp"

using namespace std;

class SymbolInfo
{
public:
    EVariable* ee_var; 
    bool is_const;
    bool is_array;
    int array_size{};
    vector<int> shape;
    vector<int> value;
    SymbolInfo(EVariable* ee_var, vector<int> value={}, bool is_const=false, bool is_array=false, vector<int> shape={});
};

class EeyoreList
{
public:
    string func_name;
    int args_num;
    vector<EStmt*> decls;
    vector<EStmt*> stmts;
    vector<int> stmt_indents;
    
    EeyoreList(string func_name, int args_num);
};

typedef unordered_map<string, SymbolInfo> SymbolTable;
typedef unordered_map<string, int> FuncTable;

class ContextEeyore
{
public:
    int glob_id, temp_id, jump_id;
    vector<SymbolTable> sym_tabs;
    vector< pair<string, string> > loops;
    vector<EeyoreList> eeyore_lists;
    FuncTable func_tabs;

    ContextEeyore();
    void insert_symbol(const string& name, SymbolInfo value);
    void insert_var(string name, EVariable* ee_var, bool is_const=false);
    void assign_var(string name, int value);
    int get_var(string name);

    void insert_array(string name, EVariable* ee_var, vector<int>& shape, bool is_const=false);
    void assign_array_item(string name, int index, int value);
    void assign_array(string name, vector<int>& value);

    int get_array_item(string name, int index);

    void insert_func(const string& func_name, int return_type, int args_num=0, bool built_in=false);
    int get_func_return_type(const string& name);


    SymbolInfo& find_symbol(const string& name);
    string create_eeyore_temp_var();
    string create_eeyore_glob_var();
    string create_jump();
    void create_scope();
    void end_scope();
    void create_loop(const string& begin_loop, const string& end_loop);
    void end_loop();
    pair<string, string> get_current_loop();
    bool is_global() const;

    void insert_eeyore_decl(EStmt* decl);
    void insert_eeyore_stmt(EStmt* stmt, int indent=0);

    void fix_eeyore();
    void print_eeyore(ostream& out);
};
