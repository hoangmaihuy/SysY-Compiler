#include "globals.hpp"
#include "context_eeyore.hpp"
#include "sysy_tree.hpp"
#include "util/util.hpp"
#include "sysy.tab.hpp"
#include "eeyore.hpp"

void TreeNode::generate_eeyore(ContextEeyore& ctx, int indent)
{
}

void NCompUnit::generate_eeyore(ContextEeyore& ctx, int indent)
{
    for (auto i : body)
        i->generate_eeyore(ctx, indent);
}

void NExpression::generate_eeyore(ContextEeyore& ctx, int indent) {}

void NDeclareStmt::generate_eeyore(ContextEeyore& ctx, int indent)
{
    for (auto i : decl_list)
        i->generate_eeyore(ctx, indent);
}

void NVarDeclare::generate_eeyore(ContextEeyore& ctx, int indent)
{
    string ee_name = ctx.create_eeyore_glob_var();
    auto* ee_var = new EVariable(ee_name, false);
    ctx.insert_var(ident.name, ee_var);
    ctx.insert_decl(new EVarStmt(ee_var));
}

void NVarDeclareWithInit::generate_eeyore(ContextEeyore& ctx, int indent)
{
    string ee_name = ctx.create_eeyore_glob_var();
    auto* ee_var = new EVariable(ee_name, false);
    ctx.insert_var(ident.name, ee_var, is_const);
    ctx.insert_decl(new EVarStmt(ee_var));

    if (is_const)
    {
        int eval_value = value.eval(ctx);
        ctx.assign_var(ident.name, eval_value);
        ctx.insert_stmt(new EAssignStmt(ee_var, eval_value), indent);
    }
    else 
    {
        value.generate_eeyore(ctx, indent);
        ctx.insert_stmt(new EAssignStmt(ee_var, value.e_value), indent);
    }
}

void NArrayDeclare::generate_eeyore(ContextEeyore& ctx, int indent)
{
    vector<int> array_shape = ident.get_shape(ctx);
    int array_size = get_array_size(array_shape);
    string ee_name = ctx.create_eeyore_glob_var();
    auto* ee_var = new EVariable(ee_name, false);
    vector<int> values(array_size, 0);

    ctx.insert_array(ident.name, ee_var, array_shape);
    ctx.assign_array(ident.name, values);
    ctx.insert_decl(new EVarArrayStmt(ee_var, array_size * INT_SIZE));
}

void NArrayDeclareWithInit::generate_eeyore(ContextEeyore& ctx, int indent)
{
    vector<int> array_shape = ident.get_shape(ctx);
    int array_size = get_array_size(array_shape);

    string ee_name = ctx.create_eeyore_glob_var();
    auto* ee_var = new EVariable(ee_name, false);
    ctx.insert_array(ident.name, ee_var, array_shape, is_const);

    ctx.insert_decl(new EVarArrayStmt(ee_var, array_size * INT_SIZE));

    if (is_const)
    {
        // can eval at compile time
        vector<int> init_values(array_size, 0);
        value.write_values(ctx, 0, array_shape, init_values);
        ctx.assign_array(ident.name, init_values);
        for (int i = 0; i < array_size; i++)
        {
            auto* item_name = new EArrayItem(ee_var, new ENumber(i * INT_SIZE));
            ctx.insert_stmt(new EAssignStmt(item_name, init_values[i]), indent);
        }
    }
    else 
    {
        // init all array as 0 
        for (int i = 0; i < array_size; i++)
        {
            auto* item_name = new EArrayItem(ee_var, new ENumber(i * INT_SIZE));
            ctx.insert_stmt(new EAssignStmt(item_name, 0), indent);
        }
        value.generate_eeyore(ctx, ee_var, array_shape, 0, indent);
    }
}

void NArrayDeclareInitValue::generate_eeyore(ContextEeyore& ctx, EVariable* ee_var, vector<int>& shape, int start_index, int indent)
{
    int array_size = get_array_size(shape);
    int sub_array_size = array_size /= shape[0];
    vector<int> sub_shape = shape;
    sub_shape.erase(sub_shape.begin());

    for (auto & i : value_list)
    {
        auto* value = (NArrayDeclareInitValue*)i;
        if (value->is_number) 
        {
            value->value->generate_eeyore(ctx, indent);
            auto* item_name = new EArrayItem(ee_var, new ENumber(start_index * INT_SIZE));
            auto* value_name = (ENumber*)value->value->e_value;
            ctx.insert_stmt(new EAssignStmt(item_name, value_name), indent);
            start_index++;
        }
        else 
        {
            value->generate_eeyore(ctx, ee_var, sub_shape, start_index, indent);
            start_index += sub_array_size;
        }
    }
}

void NCondExpr::generate_eeyore(ContextEeyore& ctx, int indent)
{
    value.generate_eeyore(ctx, indent);
    e_value = value.e_value;
}

void NBinaryExpr::generate_eeyore(ContextEeyore& ctx, int indent)
{
    lhs.generate_eeyore(ctx, indent);
    string ee_name = ctx.create_eeyore_temp_var();
    e_value = new EVariable(ee_name);
    ctx.insert_decl(new EVarStmt((EVariable *) e_value));

    if (op == AND)
    {
        string end_jump = ctx.create_jump();
        ctx.insert_stmt(new EAssignStmt(e_value, lhs.e_value), indent);
        ctx.insert_stmt(new EConditionalJump(end_jump, e_value, false), indent);
        rhs.generate_eeyore(ctx, indent);
        ctx.insert_stmt(new EBinaryExpr(e_value, e_value, op, rhs.e_value), indent);
        ctx.insert_stmt(new EJumpLabel(end_jump), indent);
    }
    else if (op == OR)
    {
        string end_jump = ctx.create_jump();
        ctx.insert_stmt(new EAssignStmt(e_value, lhs.e_value), indent);
        ctx.insert_stmt(new EConditionalJump(end_jump, e_value, true), indent);
        rhs.generate_eeyore(ctx, indent);
        ctx.insert_stmt(new EBinaryExpr(e_value, e_value, op, rhs.e_value), indent);
        ctx.insert_stmt(new EJumpLabel(end_jump), indent);
    }
    else 
    {
        rhs.generate_eeyore(ctx, indent);
        ctx.insert_stmt(new EBinaryExpr(e_value, lhs.e_value, op, rhs.e_value), indent);
    }

}

void NUnaryExpr::generate_eeyore(ContextEeyore& ctx, int indent)
{
    rhs.generate_eeyore(ctx, indent);
    string ee_name = ctx.create_eeyore_temp_var();
    e_value = new EVariable(ee_name);
    ctx.insert_decl(new EVarStmt(e_value));
    ctx.insert_stmt(new EUnaryExpr(e_value, op, rhs.e_value), indent);
}

void NNumber::generate_eeyore(ContextEeyore& ctx, int indent)
{
    e_value = new ENumber(value);
}

void NIdentifier::generate_eeyore(ContextEeyore& ctx, int indent)
{
    generate_eeyore(ctx, indent, false);
}

void NIdentifier::generate_eeyore(ContextEeyore& ctx, int indent, bool is_lhs)
{
    auto symbol = ctx.find_symbol(name);
    e_value = symbol.ee_var;
}

void NArrayIdentifier::generate_eeyore(ContextEeyore& ctx, int indent)
{
    generate_eeyore(ctx, indent, false);
}

void NArrayIdentifier::generate_eeyore(ContextEeyore& ctx, int indent, bool is_lhs)
{
    auto symbol = ctx.find_symbol(ident.name);
    vector<int> array_shape = symbol.shape;

    for (auto i : shape)
        i->generate_eeyore(ctx, indent);

    auto* index_name = new EVariable(ctx.create_eeyore_temp_var());
    ctx.insert_decl(new EVarStmt(index_name));
    ctx.insert_stmt(new EAssignStmt(index_name, 0), indent);
    
    int array_size = get_array_size(array_shape);
    auto* tmp_name = new EVariable(ctx.create_eeyore_temp_var());
    ctx.insert_decl(new EVarStmt(tmp_name));
    for (int i = 0; i < shape.size(); i++)
    {
        array_size /= array_shape[i];
        ctx.insert_stmt(new EBinaryExpr(tmp_name, shape[i]->e_value, MUL, new ENumber(array_size)), indent);
        ctx.insert_stmt(new EBinaryExpr(index_name, index_name, PLUS, tmp_name), indent);
    }

    ctx.insert_stmt(new EBinaryExpr(index_name, index_name, MUL, new ENumber(INT_SIZE)), indent);
    
    auto* item_name = new EArrayItem(symbol.ee_var, index_name);
    if (!is_lhs)
    {
        e_value = new EVariable(ctx.create_eeyore_temp_var());
        ctx.insert_decl(new EVarStmt(e_value));
        ctx.insert_stmt(new EAssignStmt(e_value, item_name), indent);
    }
    else 
    {
        e_value = item_name;
    }
}

void NBlock::generate_eeyore(ContextEeyore& ctx, int indent)
{
    ctx.create_scope();
    for (auto stmt : body)
        stmt->generate_eeyore(ctx, indent+1);
    ctx.end_scope();
}

void NFuncDef::generate_eeyore(ContextEeyore& ctx, int indent)
{
    string func_name = ident.name;
    int args_num = args.args.size();
    ctx.insert_func(func_name, return_type, args_num);

    args_num = 0; 
    // create new scope for function arguments
    ctx.create_scope();
    for (auto arg : args.args)
    {
        string ee_name = "p" + to_string(args_num++);
        auto* ee_var = new EVariable(ee_name, false);
        if (!arg->is_array)
        {
            string arg_name = arg->ident.name;
            ctx.insert_var(arg_name, ee_var);
        }
        else 
        {
            auto& array_ident = (NArrayIdentifier&)arg->ident;
            vector<int> array_shape = array_ident.get_shape(ctx);
            string arg_name = array_ident.ident.name;
            ctx.insert_array(arg_name, ee_var, array_shape);
        }
    }
    body.generate_eeyore(ctx, indent);
    if (return_type == VOID)
        ctx.insert_stmt(new EReturnStmt(), indent + 1);
    else
        ctx.insert_stmt(new EReturnStmt(new ENumber(0)), indent + 1);
    ctx.end_scope();
}

void NFuncCall::generate_eeyore(ContextEeyore& ctx, int indent)
{
    string func_name = ident.name;
    for (auto arg : args.args)
        arg->generate_eeyore(ctx, indent);
    for (auto arg : args.args)
    {
        ctx.insert_stmt(new EParamStmt(arg->e_value), indent);
    }
    int return_type = ctx.get_func_return_type(func_name);
    if (return_type == VOID)
    {
        e_value = new EFuncCall(func_name);
        ctx.insert_stmt(new EFuncCall(func_name), indent);
    }
    else 
    {
        e_value = new EVariable(ctx.create_eeyore_temp_var());
        ctx.insert_decl(new EVarStmt(e_value));
        ctx.insert_stmt(new EAssignStmt(e_value, new EFuncCall(func_name)), indent);
    }
}

void NAssignStmt::generate_eeyore(ContextEeyore& ctx, int indent)
{
    lhs.generate_eeyore(ctx, indent, true);
    rhs.generate_eeyore(ctx, indent);
    ctx.insert_stmt(new EAssignStmt(lhs.e_value, rhs.e_value), indent);
}

void NIfStmt::generate_eeyore(ContextEeyore& ctx, int indent)
{
    cond.generate_eeyore(ctx, indent);
    string else_jump = ctx.create_jump();
    ctx.insert_stmt(new EConditionalJump(else_jump, cond.e_value, false), indent);
    then_stmt.generate_eeyore(ctx, indent+1);
    ctx.insert_stmt(new EJumpLabel(else_jump), indent);
}

void NIfElseStmt::generate_eeyore(ContextEeyore& ctx, int indent)
{
    cond.generate_eeyore(ctx, indent);
    string else_jump = ctx.create_jump();
    string end_else_jump = ctx.create_jump();

    ctx.insert_stmt(new EConditionalJump(else_jump, cond.e_value, false), indent);
    then_stmt.generate_eeyore(ctx, indent+1);
    ctx.insert_stmt(new EUnconditionalJump(end_else_jump), indent + 1);
    ctx.insert_stmt(new EJumpLabel(else_jump), indent);
    else_stmt.generate_eeyore(ctx, indent+1);
    ctx.insert_stmt(new EJumpLabel(end_else_jump), indent);
}

void NReturnStmt::generate_eeyore(ContextEeyore& ctx, int indent)
{
    if (value) 
    {
        value->generate_eeyore(ctx, indent);
        ctx.insert_stmt(new EReturnStmt(value->e_value), indent);
    }
    else 
    {
        ctx.insert_stmt(new EReturnStmt(), indent);
    }
}

void NWhileStmt::generate_eeyore(ContextEeyore& ctx, int indent)
{
    string begin_loop = ctx.create_jump();
    string end_loop = ctx.create_jump();
    ctx.create_loop(begin_loop, end_loop);

    ctx.insert_stmt(new EJumpLabel(begin_loop), indent);
    cond.generate_eeyore(ctx, indent+1);

    ctx.insert_stmt(new EConditionalJump(end_loop, cond.e_value, false), indent + 1);
    do_stmt.generate_eeyore(ctx, indent+1);
    ctx.insert_stmt(new EUnconditionalJump(begin_loop), indent + 1);
    ctx.insert_stmt(new EJumpLabel(end_loop), indent);

    ctx.end_loop();
}

void NContinueStmt::generate_eeyore(ContextEeyore& ctx, int indent)
{
    pair<string, string> loop = ctx.get_current_loop();
    ctx.insert_stmt(new EUnconditionalJump(loop.first), indent);
}

void NBreakStmt::generate_eeyore(ContextEeyore& ctx, int indent)
{
    pair<string, string> loop = ctx.get_current_loop();
    ctx.insert_stmt(new EUnconditionalJump(loop.second), indent);
}

void NVoidStmt::generate_eeyore(ContextEeyore& ctx, int indent)
{

}

void NEvalStmt::generate_eeyore(ContextEeyore& ctx, int indent)
{
    value.generate_eeyore(ctx, indent);
}
