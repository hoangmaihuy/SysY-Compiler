#include "globals.hpp"
#include "symtab.hpp"
#include "tree.hpp"
#include "util.hpp"
#include "source.tab.hpp"

string EVarStmt(string name, int size=0)
{
    if (size)
        return "var " + to_string(size) + " " + name;
    else 
        return "var " + name;
}

string EBinaryExpr(string res, string lhs, int op, string rhs)
{
    return res + " = " + lhs + " " + get_token_str(op) + " " + rhs;
}

string EUnaryExpr(string res, int op, string rhs)
{
    return res + " = " + get_token_str(op) + rhs;
}

string EParamStmt(string name)
{
    return "param " + name;
}

string EFuncCall(string func_name)
{
    return "call f_" + func_name;
}

string ECondExpr(string cond_name, bool value)
{
    if (value)
        return cond_name + " == 1";
    else
        return cond_name + " == 0"; 
}

string EJumpLoc(string loc)
{
    return loc + ":";
}

string EGotoStmt(string loc, string cond_name="", bool value=false)
{
    if (cond_name == "")
        return "goto " + loc;
    else 
    {
        string cond_expr = ECondExpr(cond_name, value);
        return "if " + cond_expr + " goto " + loc;
    }
}

string EReturnStmt(string value="")
{
    return "return " + value;
}

void TreeNode::generate_eeyore(Context& ctx, int indent)
{
}

void NCompUnit::generate_eeyore(Context& ctx, int indent)
{
    for (auto i : body)
        i->generate_eeyore(ctx, indent);
}

void NExpression::generate_eeyore(Context& ctx, int indent) {}

void NDeclareStmt::generate_eeyore(Context& ctx, int indent)
{
    for (auto i : decl_list)
        i->generate_eeyore(ctx, indent);
}

void NVarDeclare::generate_eeyore(Context& ctx, int indent)
{
    string ee_name = ctx.create_eeyore_glob_var();
    ctx.insert_var(ident.name, ee_name);

    ctx.insert_eeyore_decl(EVarStmt(ee_name));
    ctx.insert_eeyore_stmt(EUnaryExpr(ee_name, 0, "0"), indent);
}

void NVarDeclareWithInit::generate_eeyore(Context& ctx, int indent)
{
    string ee_name = ctx.create_eeyore_glob_var();
    ctx.insert_var(ident.name, ee_name, is_const);
    ctx.insert_eeyore_decl(EVarStmt(ee_name));

    if (is_const)
    {
        int eval_value = value.eval(ctx);
        ctx.assign_var(ident.name, eval_value);
        ctx.insert_eeyore_stmt(EUnaryExpr(ee_name, 0, to_string(eval_value)), indent);
    }
    else 
    {
        value.generate_eeyore(ctx, indent);
        ctx.insert_eeyore_stmt(EUnaryExpr(ee_name, 0, value.ee_name), indent);
    }

}

void NArrayDeclare::generate_eeyore(Context& ctx, int indent)
{
    vector<int> array_shape = ident.get_shape(ctx);
    int array_size = get_array_size(array_shape);
    string ee_name = ctx.create_eeyore_glob_var();
    vector<int> values(array_size, 0);

    ctx.insert_array(ident.name, ee_name, array_shape);
    ctx.assign_array(ident.name, values);
    ctx.insert_eeyore_decl(EVarStmt(ee_name, array_size * INT_SIZE));

    for (int i = 0; i < array_size; i++)
    {
        string item_name = get_array_item_eeyore(ee_name, i);
        ctx.insert_eeyore_stmt(EUnaryExpr(item_name, 0, "0"), indent);
    }
}

void NArrayDeclareWithInit::generate_eeyore(Context& ctx, int indent)
{
    vector<int> array_shape = ident.get_shape(ctx);
    int array_size = get_array_size(array_shape);

    string ee_name = ctx.create_eeyore_glob_var();
    ctx.insert_array(ident.name, ee_name, array_shape, is_const);

    ctx.insert_eeyore_decl(EVarStmt(ee_name, array_size * INT_SIZE));

    if (is_const)
    {
        // can eval at compile time
        vector<int> init_values(array_size, 0);
        value.write_values(ctx, 0, array_shape, init_values);
        ctx.assign_array(ident.name, init_values);
        for (int i = 0; i < array_size; i++)
        {
            string item_name = get_array_item_eeyore(ee_name, i);
            ctx.insert_eeyore_stmt(EUnaryExpr(item_name, 0, to_string(init_values[i])), indent);
        }
    }
    else 
    {
        // init all array as 0 
        for (int i = 0; i < array_size; i++)
        {
            string item_name = get_array_item_eeyore(ee_name, i);
            ctx.insert_eeyore_stmt(EUnaryExpr(item_name, 0, "0"), indent);
        }
        value.generate_eeyore(ctx, ee_name, array_shape, 0, indent);
    }
}

void NArrayDeclareInitValue::generate_eeyore(Context& ctx, string ee_name, vector<int>& shape, int start_index, int indent)
{
    int array_size = get_array_size(shape);
    int sub_array_size = array_size /= shape[0];
    vector<int> sub_shape = shape;
    sub_shape.erase(sub_shape.begin());

    for (int i = 0; i < value_list.size(); i++)
    {
        NArrayDeclareInitValue* value = (NArrayDeclareInitValue*)value_list[i];
        if (value->is_number) 
        {
            value->value->generate_eeyore(ctx, indent);
            string item_name = get_array_item_eeyore(ee_name, start_index++);
            string value_name = value->value->ee_name;
            ctx.insert_eeyore_stmt(EUnaryExpr(item_name, 0, value_name), indent);
        }
        else 
        {
            value->generate_eeyore(ctx, ee_name, sub_shape, start_index, indent);
            start_index += sub_array_size;
        }
    }
}

void NCondExpr::generate_eeyore(Context& ctx, int indent)
{
    value.generate_eeyore(ctx, indent);
    ee_name = value.ee_name;
}

void NBinaryExpr::generate_eeyore(Context& ctx, int indent)
{
    lhs.generate_eeyore(ctx, indent);
    rhs.generate_eeyore(ctx, indent);
    this->ee_name = ctx.create_eeyore_temp_var();

    ctx.insert_eeyore_decl(EVarStmt(this->ee_name));
    ctx.insert_eeyore_stmt(EBinaryExpr(this->ee_name, lhs.ee_name, op, rhs.ee_name), indent);
}

void NUnaryExpr::generate_eeyore(Context& ctx, int indent)
{
    rhs.generate_eeyore(ctx, indent);
    this->ee_name = ctx.create_eeyore_temp_var();
    ctx.insert_eeyore_decl(EVarStmt(ee_name));
    ctx.insert_eeyore_stmt(EUnaryExpr(ee_name, op, rhs.ee_name), indent);
}

void NNumber::generate_eeyore(Context& ctx, int indent)
{
    this->ee_name = to_string(value);
}

void NIdentifier::generate_eeyore(Context& ctx, int indent)
{
    auto symbol = ctx.find_symbol(name);
    ee_name = symbol.ee_name;
}

void NArrayIdentifier::generate_eeyore(Context& ctx, int indent)
{
    auto symbol = ctx.find_symbol(ident.name);
    vector<int> array_shape = symbol.shape;

    for (auto i : shape)
        i->generate_eeyore(ctx, indent);

    string index_name = ctx.create_eeyore_temp_var();
    ctx.insert_eeyore_decl(EVarStmt(index_name));
    ctx.insert_eeyore_stmt(EUnaryExpr(index_name, 0, "0"), indent);
    
    int array_size = get_array_size(array_shape);
    string tmp_name = ctx.create_eeyore_temp_var();
    ctx.insert_eeyore_decl(EVarStmt(tmp_name));
    for (int i = 0; i < array_shape.size(); i++)
    {
        array_size /= array_shape[i];
        ctx.insert_eeyore_stmt(EBinaryExpr(tmp_name, shape[i]->ee_name, MUL, to_string(array_size)),indent);
        ctx.insert_eeyore_stmt(EBinaryExpr(index_name, index_name, PLUS, tmp_name), indent);
    }
    ctx.insert_eeyore_stmt(EBinaryExpr(index_name, index_name, MUL, "4"), indent);
    
    ee_name = ctx.create_eeyore_temp_var();
    string rhs = symbol.ee_name + " [" + index_name + "]";
    ctx.insert_eeyore_decl(EVarStmt(ee_name));
    ctx.insert_eeyore_stmt(EUnaryExpr(ee_name, 0, rhs), indent);
}

void NBlock::generate_eeyore(Context& ctx, int indent)
{
    ctx.create_scope();
    for (auto stmt : body)
        stmt->generate_eeyore(ctx, indent+1);
    ctx.end_scope();
}

void NFuncDef::generate_eeyore(Context& ctx, int indent)
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
        if (!arg->is_array)
        {
            string arg_name = arg->ident.name;
            ctx.insert_var(arg_name, ee_name);
        }
        else 
        {
            NArrayIdentifier& array_ident = (NArrayIdentifier&)arg->ident;
            vector<int> array_shape = array_ident.get_shape(ctx);
            string arg_name = array_ident.ident.name;
            ctx.insert_array(arg_name, ee_name, array_shape);
        }
    }
    body.generate_eeyore(ctx, indent);
    ctx.end_scope();
}

void NFuncCall::generate_eeyore(Context& ctx, int indent)
{
    string func_name = ident.name;
    for (auto arg : args.args)
        arg->generate_eeyore(ctx, indent);
    for (auto arg : args.args)
    {
        ctx.insert_eeyore_stmt(EParamStmt(arg->ee_name), indent);
    }
    int return_type = ctx.get_func_return_type(func_name);
    if (return_type == VOID)
    {
        ee_name = EFuncCall(func_name);
        ctx.insert_eeyore_stmt(EFuncCall(func_name), indent);
    }
    else 
    {
        ee_name = ctx.create_eeyore_temp_var();
        ctx.insert_eeyore_decl(EVarStmt(ee_name));
        ctx.insert_eeyore_stmt(EUnaryExpr(ee_name, 0, EFuncCall(func_name)), indent);
    }
}

void NAssignStmt::generate_eeyore(Context& ctx, int indent)
{
    lhs.generate_eeyore(ctx, indent);
    rhs.generate_eeyore(ctx, indent);
    ctx.insert_eeyore_stmt(EUnaryExpr(lhs.ee_name, 0, rhs.ee_name), indent);
}

void NIfStmt::generate_eeyore(Context& ctx, int indent)
{
    cond.generate_eeyore(ctx, indent);
    string else_jump = ctx.create_jump();
    ctx.insert_eeyore_stmt(EGotoStmt(else_jump, cond.ee_name, false));
    then_stmt.generate_eeyore(ctx, indent+1);
    ctx.insert_eeyore_stmt(EJumpLoc(else_jump), indent);
}

void NIfElseStmt::generate_eeyore(Context& ctx, int indent)
{
    cond.generate_eeyore(ctx, indent);
    string else_jump = ctx.create_jump();
    string end_else_jump = ctx.create_jump();

    ctx.insert_eeyore_stmt(EGotoStmt(else_jump, cond.ee_name, false), indent);
    then_stmt.generate_eeyore(ctx, indent+1);
    ctx.insert_eeyore_stmt(EGotoStmt(end_else_jump), indent+1);
    ctx.insert_eeyore_stmt(EJumpLoc(else_jump), indent);
    else_stmt.generate_eeyore(ctx, indent+1);
    ctx.insert_eeyore_stmt(EJumpLoc(end_else_jump), indent);
}

void NReturnStmt::generate_eeyore(Context& ctx, int indent)
{
    if (value) 
    {
        value->generate_eeyore(ctx, indent);
        ctx.insert_eeyore_stmt(EReturnStmt(value->ee_name), indent);
    }
    else 
    {
        ctx.insert_eeyore_stmt(EReturnStmt(), indent);
    }
}

void NWhileStmt::generate_eeyore(Context& ctx, int indent)
{
    string begin_loop = ctx.create_jump();
    string end_loop = ctx.create_jump();
    ctx.create_loop(begin_loop, end_loop);

    ctx.insert_eeyore_stmt(EJumpLoc(begin_loop), indent);
    cond.generate_eeyore(ctx, indent+1);

    ctx.insert_eeyore_stmt(EGotoStmt(end_loop, cond.ee_name, false), indent+1);
    do_stmt.generate_eeyore(ctx, indent+1); 
    ctx.insert_eeyore_stmt(EGotoStmt(begin_loop), indent+1);
    ctx.insert_eeyore_stmt(EJumpLoc(end_loop), indent);

    ctx.end_loop();
}

void NContinueStmt::generate_eeyore(Context& ctx, int indent)
{
    pair<string, string> loop = ctx.get_current_loop();
    ctx.insert_eeyore_stmt(EGotoStmt(loop.first), indent);
}

void NBreakStmt::generate_eeyore(Context& ctx, int indent)
{
    pair<string, string> loop = ctx.get_current_loop();
    ctx.insert_eeyore_stmt(EGotoStmt(loop.second), indent);
}

void NVoidStmt::generate_eeyore(Context& ctx, int indent)
{

}

void NEvalStmt::generate_eeyore(Context& ctx, int indent)
{
    value.generate_eeyore(ctx, indent);
}
