//
// Created by mew on 10/12/2020.
//

#include "register_allocator.hpp"
#include "context_tigger.hpp"
#include "util.hpp"

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
    register_map["0"] = ZERO_REG;
    register_value[ZERO_REG] = "0";
    for (const auto& reg_name : FREE_REG_NAME) free_register.insert(reg_name);
}

bool RegisterAllocator::is_in_register(const string& var_name)
{
    return register_map.find(var_name) != register_map.end();
}

bool RegisterAllocator::is_allocated(const string &var_name)
{
    return allocated_register_map.find(var_name) != allocated_register_map.end();
}

string RegisterAllocator::get_variable_register(ContextTigger &ctx, TiggerFunc &func, const string& e_name, const string& exclude_reg)
{
    // already in register
    if (e_name == "0") return ZERO_REG;
    if (is_in_register(e_name))
        return register_map[e_name];
    // not in register
    string reg_name;
    if (e_name[0] == 'p')
    {
        reg_name = e_name;
        reg_name[0] = 'a';
        return reg_name;
    }
    if (is_allocated(e_name) && allocated_register_map[e_name] != exclude_reg)
    {
        reg_name = allocated_register_map[e_name];
    }
    else
    {
        for (auto& reg : FREE_REG_NAME)
        {
            if (!register_has_value(reg) && reg != exclude_reg) return reg;
        }
        int last_use = 0;
        for (auto& reg : FREE_REG_NAME)
        {
            string reg_value = register_value[reg];
            auto it = func.live_interval.find(reg_value);
            if (it == func.live_interval.end())
            {
                reg_name = reg;
                break;
            }
            else if (it->second.second > last_use)
            {
                reg_name = reg;
                last_use = it->second.second;
            }
        }
    }
    clear_register(ctx, func, reg_name, e_name);
    return reg_name;
}

bool RegisterAllocator::register_has_value(const string &reg_name)
{
    return register_value.find(reg_name) != register_value.end();
}

void RegisterAllocator::load_variable(ContextTigger &ctx, TiggerFunc &func, const string &e_name,
                                      const string &reg_name)
{
    if (is_in_register(e_name) && register_map[e_name] == reg_name) return;
    if (e_name[0] == 'p') return;
    bool is_array = ctx.is_array(e_name);
    if (ctx.is_global_var(e_name))
    {
        string t_name = ctx.find_var(e_name);
        if (!is_array)
            func.stmts.emplace_back(new TLoadGlobal(t_name, reg_name));
        else
            func.stmts.emplace_back(new TLoadaddrGlobal(t_name, reg_name));
    }
    else if (name_is_number(e_name))
    {
        func.stmts.emplace_back(new TAssignNumber(reg_name, stoi(e_name)));
    }
    else // stack variable
    {
        int stack_loc = func.get_stack_loc(e_name);
        if (!is_array)
            func.stmts.emplace_back(new TLoadStack(stack_loc, reg_name));
        else
            func.stmts.emplace_back(new TLoadaddrStack(stack_loc, reg_name));
    }
    map_reg_var(reg_name, e_name);
}

void RegisterAllocator::store_register(ContextTigger &ctx, TiggerFunc &func, const string &reg_name, const string &e_name, bool is_spill)
{
    if (name_is_number(e_name)) return; // number not need to spill
    if (ctx.is_global_var(e_name))
    {
        if (is_spill) return;
        string t_name = ctx.find_var(e_name);
        func.stmts.emplace_back(new TLoadaddrGlobal(t_name, ADDRESS_REG));
        func.stmts.emplace_back(new TArrayWrite(ADDRESS_REG, 0, reg_name));
    }
    else if (is_spill)
    {
        int stack_loc = func.get_stack_loc(e_name);
        func.stmts.emplace_back(new TStoreStack(reg_name, stack_loc));
    }
}

void
RegisterAllocator::clear_register(ContextTigger &ctx, TiggerFunc &func, const string &reg_name, const string &e_name)
{
    if (register_has_value(reg_name))
    {
        string spill_name = register_value[reg_name];
        if (spill_name == e_name) return;
        store_register(ctx, func, reg_name, spill_name, true);
    }
}

void RegisterAllocator::map_reg_var(const string &reg_name, const string &var_name)
{
    if (name_is_number(var_name)) return;
    register_map[var_name] = reg_name;
    register_value[reg_name] = var_name;
}

