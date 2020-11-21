#include "util.hpp"
#include "tree.hpp"
#include "source.tab.hpp"

string get_token_str(int token)
{
    switch (token)
    {
        case INT: return "int"; break;
        case VOID: return "void"; break;
        case ASSIGN: return "="; break;
        case EQ: return "=="; break;
        case NE: return "!="; break;
        case LT: return "<"; break;
        case GT: return ">"; break;
        case LE: return "<="; break;
        case GE: return ">="; break;
        case AND: return "&&"; break;
        case OR: return "||"; break;
        case PLUS: return "+"; break;
        case MINUS: return "-"; break;
        case MUL: return "*"; break;
        case DIV: return "/"; break;
        case MOD: return "%"; break;
        case NOT: return "!"; break;
        default: return ""; break;
    }
}

string get_file_prefix(string filename)
{
    string prefix = filename;
    while (prefix.back() != '.') prefix.pop_back();
    return prefix;
}

int get_array_size(const vector<int>& shape)
{
    int size = 1;
    for (auto i : shape) size *= i;
    return size;
}

int get_array_index(const vector<int>& shape, const vector<int>& indexes)
{
    int array_size = get_array_size(shape);
    int index = 0;
    for (int i = 0; i < shape.size(); i++)
    {
        array_size /= shape[i];
        index += indexes[i] * array_size;
    }
    return index;
}

string get_array_item_eeyore(string ee_name, int index)
{
    return ee_name + " [" + to_string(index*INT_SIZE) + "]";
}