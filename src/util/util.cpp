#include "util.hpp"

#include <utility>
#include "sysy_tree.hpp"
#include "sysy.tab.hpp"

string get_token_str(int token)
{
    switch (token)
    {
        case INT: return "int";
        case VOID: return "void";
        case ASSIGN: return "=";
        case EQ: return "==";
        case NE: return "!=";
        case LT: return "<";
        case GT: return ">";
        case LE: return "<=";
        case GE: return ">=";
        case AND: return "&&";
        case OR: return "||";
        case PLUS: return "+";
        case MINUS: return "-";
        case MUL: return "*";
        case DIV: return "/";
        case MOD: return "%";
        case NOT: return "!";
        default: return "";
    }
}

string get_file_prefix(string filename)
{
    string prefix = std::move(filename);
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

void concat_string_vector(vector<string>& a, const vector<string>& b)
{
    a.insert(a.end(), b.begin(), b.end());
}

bool name_is_number(const string &name)
{
    return isdigit(name[0]);
}

bool is_param(const string &name)
{
    return name[0] == 'p';
}
