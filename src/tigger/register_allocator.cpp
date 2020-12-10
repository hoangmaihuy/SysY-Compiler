//
// Created by mew on 10/12/2020.
//

#include "register_allocator.hpp"

const vector<string> RegisterAllocator::FREE_REG_NAME = {
        "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11",
        "t0", "t1", "t2", "t3", "t4", "t5", "t6"
};

const int RegisterAllocator::FREE_REG_NUM = FREE_REG_NAME.size();

const vector<string> RegisterAllocator::CALLER_SAVE_REG = {
        "t0", "t1", "t2", "t3", "t4", "t5", "t6",
        "a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7"
};

const vector<string> RegisterAllocator::CALLEE_SAVE_REG = {
        "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11"
};

RegisterAllocator::RegisterAllocator()
{

}

bool RegisterAllocator::has_free_register()
{
    return !free_register.empty();
}

string RegisterAllocator::get_free_register()
{
    return *free_register.begin();
}


void RegisterAllocator::alloc_register(string var_name, string reg_name)
{
    register_map[var_name] = reg_name;
    free_register.erase(reg_name);
}

string RegisterAllocator::dealloc_register(string var_name)
{
    string reg_name = register_map[var_name];
    free_register.insert(reg_name);
    register_map.erase(var_name);
    return reg_name;
}

void RegisterAllocator::release_register(string var_name)
{
    string reg_name = register_map[var_name];
    free_register.insert(reg_name);
}
