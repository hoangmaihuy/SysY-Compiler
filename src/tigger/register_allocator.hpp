#ifndef SYSY_COMPILER_REGISTER_ALLOCATOR_HPP
#define SYSY_COMPILER_REGISTER_ALLOCATOR_HPP

#include "globals.hpp"

class RegisterAllocator
{
public:
    static const vector<string> FREE_REG_NAME;
    static const int FREE_REG_NUM;
    static const vector<string> CALLER_SAVE_REG;
    static const vector<string> CALLEE_SAVE_REG;
    unordered_map<string, string> register_map; // eeyore_name to register
    set<string> free_register;

    RegisterAllocator();
    bool has_free_register();
    string get_free_register();
    void alloc_register(string var_name, string reg_name);
    string dealloc_register(string var_name);
    void release_register(string var_name);
};

#endif //SYSY_COMPILER_REGISTER_ALLOCATOR_HPP