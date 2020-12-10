#include "context_tigger.hpp"

#include <utility>



ContextTigger::ContextTigger()
{
    var_id = 0;
}

TiggerFunc::TiggerFunc(string func_name, int args_num) : func_name(std::move(func_name)), args_num(args_num)
{
    stack_size = 0;
}

void TiggerFunc::register_allocation(EeyoreFunc &eeyore_func)
{
    auto& live_intervals = eeyore_func.live_intervals;
    auto& eeyore_decls = eeyore_func.decls;
    auto& eeyore_stmts = eeyore_func.stmts;

    // stack size for T?
    for (auto decl : eeyore_decls)
    {
        if (decl->get_type() == E_VAR_STMT)
        {
            string ee_name = ((EVarStmt*)decl)->name->to_string();
            if (ee_name[0] == 't') // temporary var
                continue;
            new_stack_var(ee_name);
        }
        else if (decl->get_type() == E_VAR_ARRAY_STMT)
        {
            string ee_name = ((EVarArrayStmt*)decl)->name->to_string();
            int size = ((EVarArrayStmt*)decl)->size / 4;
            new_stack_var(ee_name, size);
        }
    }

    // linear scan register allocation
    set<LiveInterval, IntervalCmp> active_heap;

    for (auto& interval : live_intervals)
    {
        string ee_name = interval.name;
        // expire old intervals
        while (!active_heap.empty())
        {
            auto top = *active_heap.begin();
            if (top.tout <= interval.tin)
            {
                register_allocator.release_register(top.name);
                active_heap.erase(active_heap.begin());
            }
            else break;
        }
        if (!register_allocator.has_free_register())
        {
            auto spill = *active_heap.rbegin();
            if (spill.tout > interval.tout)
            {
                auto reg_name = register_allocator.dealloc_register(spill.name);
                register_allocator.alloc_register(ee_name, reg_name);
                new_stack_var(spill.name);
                active_heap.erase(spill);
                active_heap.insert(interval);
            }
            else
            {
                new_stack_var(ee_name);
            }
        }
        else
        {
            // alloc free register
            auto reg_name = register_allocator.get_free_register();
            register_allocator.alloc_register(ee_name, reg_name);
        }
    }
}

void TiggerFunc::new_stack_var(const string& name, int size)
{
    if (check_var_in_stack(name)) return;
    int stack_loc = stack_size;
    stack_map[name] = stack_loc;
    stack_size += size;
}

bool TiggerFunc::check_var_in_stack(const string& name)
{
    return stack_map.find(name) != stack_map.end();
}

void ContextTigger::insert_func(string func_name, int args_num)
{
    tigger_funcs.emplace_back(TiggerFunc(func_name, args_num));
}

string ContextTigger::new_global_var()
{
    return "v" + to_string(var_id++);
}

void ContextTigger::insert_var(const string& ee_name, TVariable *t_var)
{
    symtab.insert({ee_name, t_var});
}

TiggerFunc &ContextTigger::get_current_func()
{
    return tigger_funcs.back();
}
