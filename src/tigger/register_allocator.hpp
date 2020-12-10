#ifndef SYSY_COMPILER_REGISTER_ALLOCATOR_HPP
#define SYSY_COMPILER_REGISTER_ALLOCATOR_HPP

#include "globals.hpp"
#include "eeyore.hpp"
#include "tigger.hpp"

#define RETURN_REG "a0"
#define ADDRESS_REG "s10"
#define CONST_REG  "s11"
#define ZERO_REG   "x0"

class RegisterAllocator
{
public:
    static const vector<string> FREE_REG_NAME;
    static const int FREE_REG_NUM;
    static const vector<string> CALLER_SAVE_REG;
    static const vector<string> CALLEE_SAVE_REG;
    unordered_map<string, string> allocated_register_map; // eeyore_name to register
    unordered_map<string, string> register_map; // eeyore_name to register
    unordered_map<string, string> register_value;
    set<string> free_register;

    RegisterAllocator();
    bool has_free_register();
    bool is_in_register(const string& var_name);
    bool is_allocated(const string& var_name);
    string get_allocated_register(const string& var_name);
    string get_free_register();
    void alloc_register(string var_name, string reg_name);
    string dealloc_register(string var_name);
    void release_register(string var_name);
    void free_all();

    string get_register(vector<TStmt*>& stmts, EValue* e_var);
};

#endif //SYSY_COMPILER_REGISTER_ALLOCATOR_HPP
