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
        default: return "undefined"; break;
    }
}