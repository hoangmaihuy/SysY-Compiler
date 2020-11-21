#include "globals.hpp"
#include "symtab.hpp"
#include "tree.hpp"
#include "source.tab.hpp"
#include "util.hpp"

int NExpression::eval(Context& ctx)
{
    return 0;
}

int NBinaryExpr::eval(Context& ctx)
{
    int lhs_val = lhs.eval(ctx);
    int rhs_val = rhs.eval(ctx);
    switch (op)
    {
        case EQ: return lhs_val == rhs_val;
        case NE: return lhs_val != rhs_val;
        case LT: return lhs_val < rhs_val;
        case GT: return lhs_val > rhs_val;
        case LE: return lhs_val <= rhs_val;
        case GE: return lhs_val >= rhs_val;
        case AND: return lhs_val && rhs_val;
        case OR: return lhs_val || rhs_val;
        case PLUS: return lhs_val + rhs_val;
        case MINUS: return lhs_val - rhs_val;
        case MUL: return lhs_val * rhs_val;
        case DIV: return lhs_val / rhs_val;
        case MOD: return lhs_val % rhs_val;
        default: return 0;
    }
    return 0;
}

int NUnaryExpr::eval(Context& ctx)
{
    int rhs_val = rhs.eval(ctx);
    switch (op)
    {
        case NOT: return !rhs_val;
        case MINUS: return -rhs_val;
        case PLUS: return +rhs_val;
    }
    return 0;
}

int NNumber::eval(Context& ctx)
{
    return value;
}

int NIdentifier::eval(Context& ctx)
{
    auto symbol = ctx.find_symbol(name);
    return symbol.value[0];
}

vector<int> NArrayIdentifier::get_shape(Context& ctx)
{
    vector<int> eval_shape;
    for (auto i : shape) eval_shape.push_back(i->eval(ctx));
    return eval_shape;
}

int NArrayIdentifier::eval(Context& ctx)
{
    auto symbol = ctx.find_symbol(name);
    auto array_shape = symbol.shape;
    int array_size = symbol.array_size;

    vector<int> indexes = get_shape(ctx);
    int index = get_array_index(array_shape, indexes);

    return symbol.value[index];
}

void NArrayDeclareInitValue::write_values(Context& ctx, int start_index, vector<int>& shape, vector<int>& init_values)
{
    int array_size = get_array_size(shape);
    int sub_array_size = array_size /= shape[0];
    vector<int> sub_shape = shape;
    sub_shape.erase(sub_shape.begin());

    for (int i = 0; i < value_list.size(); i++)
    {
        NArrayDeclareInitValue* value = (NArrayDeclareInitValue*) value_list[i];
        if (value->is_number) 
        {
            init_values[start_index++] = value->value->eval(ctx);
        }
        else 
        {
            value->write_values(ctx, start_index, sub_shape, init_values);
            start_index += sub_array_size;
        }
    }
}
