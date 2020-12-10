//
// Created by mew on 10/12/2020.
//

#include "register_allocator.hpp"

const vector<string> RegisterAllocator::FREE_REG_NAME = {
        "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9",
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
    free_all();
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
    allocated_register_map[var_name] = reg_name;
    free_register.erase(reg_name);
}

string RegisterAllocator::dealloc_register(string var_name)
{
    string reg_name = allocated_register_map[var_name];
    free_register.insert(reg_name);
    allocated_register_map.erase(var_name);
    return reg_name;
}

void RegisterAllocator::release_register(string var_name)
{
    string reg_name = allocated_register_map[var_name];
    free_register.insert(reg_name);
}

void RegisterAllocator::free_all()
{
    register_map.clear();
    register_value.clear();
    free_register.clear();
    for (const auto& reg_name : FREE_REG_NAME) free_register.insert(reg_name);
}

bool RegisterAllocator::is_in_register(const string& var_name)
{
    return register_map.find(var_name) != register_map.end();
}

string RegisterAllocator::get_register(vector<TStmt*>& stmts, EValue *e_var)
{
    int value_type = e_var->get_type();
    if (value_type == E_VARIABLE)
    {
        string var_name = ((EVariable*)e_var)->name;
        if (is_in_register(var_name))
            return register_map[var_name];
        else if (is_allocated(var_name))
            return allocated_register_map[var_name];
    }
    else if (value_type == E_NUMBER)
    {
        int value = ((ENumber*)e_var)->to_int();
        if (value == 0) return ZERO_REG;
        else
        {
            if (register_value.find(CONST_REG) != register_value.end()
            && register_value[CONST_REG] == std::to_string(value))
                return CONST_REG;
            else
            {
                register_value[CONST_REG] = std::to_string(value);
                stmts.emplace_back(new TAssignNumber(CONST_REG, value));
                return CONST_REG;
            }
        }
    }
}

bool RegisterAllocator::is_allocated(const string &var_name)
{
    return allocated_register_map.find(var_name) != allocated_register_map.end();
}

string RegisterAllocator::get_allocated_register(const string &var_name)
{
    return allocated_register_map[var_name];
}

