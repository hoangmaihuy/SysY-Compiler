#ifndef SYSY_COMPILER_REGISTER_ALLOCATOR_HPP
#define SYSY_COMPILER_REGISTER_ALLOCATOR_HPP

#include "globals.hpp"
#include "eeyore.hpp"
#include "tigger.hpp"

const string RETURN_REG = "a0";
const string ADDRESS_REG = "s10";
const string CONST_REG = "s11";
const string ZERO_REG = "x0";
const string SP_REG = "sp";
const string RA_REG = "ra";

class ContextTigger;
class TiggerFunc;

class RegisterAllocator
{
public:
    static const vector<string> FREE_REG_NAME;
    static const int FREE_REG_NUM;
    static const vector<string> CALLER_SAVE_REG;
    static const vector<string> CALLEE_SAVE_REG;
    unordered_map<string, string> allocated_register_map; // eeyore_name to register
    unordered_map<string, string> register_map; // eeyore_name to register
    unordered_map<string, string> register_value; // register to eeyore_name
    set<string> free_register;

    RegisterAllocator();
    bool has_free_register();
    bool is_in_register(const string& var_name);
    bool is_allocated(const string& var_name);
    bool register_has_value(const string& reg_name);
    string get_free_register();
    void alloc_register(string var_name, string reg_name);
    string dealloc_register(string var_name);
    void release_register(string var_name);
    void free_all();

    string get_variable_register(ContextTigger& ctx, TiggerFunc& func, const string& e_name, const string& exclude_reg="");
    void load_variable(ContextTigger& ctx, TiggerFunc& func, string e_name, const string& reg_name);
    void store_register(ContextTigger& ctx, TiggerFunc& func, const string& reg_name, const string& e_name, bool is_spill=false);
    void clear_register(ContextTigger& ctx, TiggerFunc& func, const string& reg_name, const string& e_name);
    void map_reg_var(const string& reg_name, const string& var_name);
};

#endif //SYSY_COMPILER_REGISTER_ALLOCATOR_HPP
