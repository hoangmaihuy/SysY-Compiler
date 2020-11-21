#include "globals.hpp"
#include "symtab.hpp"
#include "tree.hpp"
#include "util.hpp"
#include "source.tab.hpp"

void printDeclareVar(string name, ostream& out, int size=0)
{
    if (size)
        out << "var " << size << " " << name << "\n";
    else 
        out << "var " << name << "\n";
}

void printBinaryExpr(string res, string lhs, int op, string rhs, ostream& out)
{
    out << res << " = " << lhs << " " << get_token_str(op) << " " << rhs << "\n";
}

void printUnaryExpr(string res, int op, string rhs, ostream& out)
{
    out << res << " = " << get_token_str(op) << rhs << "\n";
}

void TreeNode::generate_eeyore(Context& ctx, int indent, ostream& out)
{
}

void NCompUnit::generate_eeyore(Context& ctx, int indent, ostream& out)
{
    for (auto i : body)
        i->generate_eeyore(ctx, indent, out);
}

void NExpression::generate_eeyore(Context& ctx, int indent, ostream& out) {}

void NDeclareStmt::generate_eeyore(Context& ctx, int indent, ostream& out)
{
    for (auto i : decl_list)
        i->generate_eeyore(ctx, indent, out);
}

void NVarDeclare::generate_eeyore(Context& ctx, int indent, ostream& out)
{
    string ee_name = ctx.create_eeyore_glob_var();
    ctx.insert_var(ident.name, ee_name);

    printSpace(indent, out);
    printDeclareVar(ee_name, out);

    printSpace(indent, out);
    printUnaryExpr(ee_name, 0, "0", out);
}

void NVarDeclareWithInit::generate_eeyore(Context& ctx, int indent, ostream& out)
{
    string ee_name = ctx.create_eeyore_glob_var();
    ctx.insert_var(ident.name, ee_name);

    printSpace(indent, out);
    printDeclareVar(ee_name, out);
    if (is_const)
    {
        int eval_value = value.eval(ctx);
        ctx.assign_var(ident.name, eval_value);
        printSpace(indent, out);
        printUnaryExpr(ee_name, 0, to_string(eval_value), out);
    }
    else 
    {
        value.generate_eeyore(ctx, indent, out);
        printSpace(indent, out);
        printUnaryExpr(ee_name, 0, value.ee_name, out);
    }

}

void NArrayDeclare::generate_eeyore(Context& ctx, int indent, ostream& out)
{
    vector<int> array_shape = ident.get_shape(ctx);
    int array_size = get_array_size(array_shape);
    string ee_name = ctx.create_eeyore_glob_var();
    vector<int> values(array_size, 0);

    ctx.insert_array(ident.name, ee_name, array_shape);
    ctx.assign_array(ident.name, values);

    printSpace(indent, out);
    printDeclareVar(ee_name, out, array_size * INT_SIZE);

    for (int i = 0; i < array_size; i++)
    {
        string item_name = get_array_item_eeyore(ee_name, i);
        printSpace(indent, out);
        printUnaryExpr(item_name, 0, "0", out);
    }
}

void NArrayDeclareWithInit::generate_eeyore(Context& ctx, int indent, ostream& out)
{
    vector<int> array_shape = ident.get_shape(ctx);
    int array_size = get_array_size(array_shape);

    string ee_name = ctx.create_eeyore_glob_var();
    ctx.insert_array(ident.name, ee_name, array_shape, is_const);

    printSpace(indent, out);
    printDeclareVar(ee_name, out, array_size * INT_SIZE);

    if (is_const)
    {
        // can eval at compile time
        vector<int> init_values(array_size, 0);
        value.write_values(ctx, 0, array_shape, init_values);
        ctx.assign_array(ident.name, init_values);
        for (int i = 0; i < array_size; i++)
        {
            string item_name = get_array_item_eeyore(ee_name, i);
            printSpace(indent, out);
            printUnaryExpr(item_name, 0, to_string(init_values[i]), out);
        }
    }
    else 
    {
        // init all array as 0 
        for (int i = 0; i < array_size; i++)
        {
            string item_name = get_array_item_eeyore(ee_name, i);
            printSpace(indent, out);
            printUnaryExpr(item_name, 0, "0", out);
        }
        value.generate_eeyore(ctx, ee_name, array_shape, 0, indent, out);
    }
}

void NArrayDeclareInitValue::generate_eeyore(Context& ctx, string ee_name, vector<int>& shape, int start_index, int indent, ostream& out)
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
            value->value->generate_eeyore(ctx, indent, out);
            string item_name = get_array_item_eeyore(ee_name, start_index++);
            printSpace(indent, out);
            printUnaryExpr(item_name, 0, value->ee_name, out);
        }
        else 
        {
            value->generate_eeyore(ctx, ee_name, sub_shape, start_index, indent, out);
            start_index += sub_array_size;
        }
    }
}

void NCondExpr::generate_eeyore(Context& ctx, int indent, ostream& out)
{

}

void NBinaryExpr::generate_eeyore(Context& ctx, int indent, ostream& out)
{
    lhs.generate_eeyore(ctx, indent, out);
    rhs.generate_eeyore(ctx, indent, out);
    this->ee_name = ctx.create_eeyore_temp_var();

    printSpace(indent, out);
    printDeclareVar(this->ee_name, out);

    printSpace(indent, out);
    printBinaryExpr(this->ee_name, lhs.ee_name, op, rhs.ee_name, out);
}

void NUnaryExpr::generate_eeyore(Context& ctx, int indent, ostream& out)
{
    rhs.generate_eeyore(ctx, indent, out);
    this->ee_name = ctx.create_eeyore_temp_var();

    printSpace(indent, out);
    printUnaryExpr(this->ee_name, op, rhs.ee_name, out);
}

void NNumber::generate_eeyore(Context& ctx, int indent, ostream& out)
{
    this->ee_name = to_string(value);
}

void NIdentifier::generate_eeyore(Context& ctx, int indent, ostream& out)
{
    auto symbol = ctx.find_symbol(name);
    ee_name = symbol.ee_name;
}

void NArrayIdentifier::generate_eeyore(Context& ctx, int indent, ostream& out)
{
    auto symbol = ctx.find_symbol(ident.name);
    vector<int> array_shape = symbol.shape;

    for (auto i : shape)
        i->generate_eeyore(ctx, indent, out);

    string index_name = ctx.create_eeyore_temp_var();
    int array_size = get_array_size(array_shape);
    for (int i = 0; i < array_shape.size(); i++)
    {
        array_size /= array_shape[i];
        printSpace(indent, out);
        out << index_name << " = " << index_name << " + " << shape[i]->ee_name << "\n";
    }

    printSpace(indent, out);
    ee_name = symbol.ee_name + " [" + index_name + "]";
}


void NBlock::generate_eeyore(Context& ctx, int indent, ostream& out)
{
    ctx.create_scope();
    for (auto stmt : body)
        stmt->generate_eeyore(ctx, indent+1, out);
    ctx.end_scope();
}

void NFuncDef::generate_eeyore(Context& ctx, int indent, ostream& out)
{
    string f_name = "f_" + ident.name;
    ctx.insert_func(ident.name, return_type);
    int args_num = 0; 
    // create new scope for function arguments
    ctx.create_scope();
    for (auto arg : args.args)
    {
        string ee_name = "p" + to_string(args_num++);
        if (!arg->is_array)
        {
            ctx.insert_var(ident.name, ee_name);
        }
        else 
        {
            auto array_ident = (NArrayIdentifier&)arg->ident;
            vector<int> array_shape = array_ident.get_shape(ctx);
            ctx.insert_array(array_ident.ident.name, ee_name, array_shape);
        }
    }

    printSpace(indent, out);
    out << f_name << " [" << args_num << "]" << "\n";
    body.generate_eeyore(ctx, indent, out);
    printSpace(indent, out);
    out << "end " << f_name << "\n";
    ctx.end_scope();
}

void NFuncCall::generate_eeyore(Context& ctx, int indent, ostream& out)
{
    string f_name = "f_" + ident.name;
    for (auto arg : args.args)
        arg->generate_eeyore(ctx, indent, out);
    for (auto arg: args.args)
    {
        printSpace(indent, out);
        out << "param " << arg->ee_name << "\n";
    }
    int return_type = ctx.get_func_return_type(ident.name);
    if (return_type == VOID)
    {
        printSpace(indent, out);
        out << "call " << f_name << "\n";
    }
    else 
    {
        ee_name = ctx.create_eeyore_temp_var();
        printSpace(indent, out);
        printDeclareVar(ee_name, out);
        printSpace(indent, out);
        printUnaryExpr(ee_name, 0, "call " + f_name, out);
    }
}

void NAssignStmt::generate_eeyore(Context& ctx, int indent, ostream& out)
{
    lhs.generate_eeyore(ctx, indent, out);
    rhs.generate_eeyore(ctx, indent, out);
    printSpace(indent, out);
    out << lhs.ee_name << " = " << rhs.ee_name << "\n";
}

void NIfStmt::generate_eeyore(Context& ctx, int indent, ostream& out)
{

}

void NIfElseStmt::generate_eeyore(Context& ctx, int indent, ostream& out)
{

}

void NReturnStmt::generate_eeyore(Context& ctx, int indent, ostream& out)
{
    printSpace(indent, out);
    if (value) 
    {
        value->generate_eeyore(ctx, indent, out);
        out << "return " << value->ee_name << "\n";
    }
    else 
        out << "return" << "\n";
}

void NWhileStmt::generate_eeyore(Context& ctx, int indent, ostream& out)
{

}

void NContinueStmt::generate_eeyore(Context& ctx, int indent, ostream& out)
{

}

void NBreakStmt::generate_eeyore(Context& ctx, int indent, ostream& out)
{

}

void NVoidStmt::generate_eeyore(Context& ctx, int indent, ostream& out)
{

}

void NEvalStmt::generate_eeyore(Context& ctx, int indent, ostream& out)
{
    value.generate_eeyore(ctx, indent, out);
}