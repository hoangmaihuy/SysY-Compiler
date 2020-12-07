#include "globals.hpp"
#include "tree.hpp"
#include "sysy.tab.hpp"
#include "util.hpp"

/* TreeNode */
void TreeNode::print(int indent, bool end, ostream& out) 
{
  this->printIndent(indent, end, out);
  out << "[TreeNode]" << std::endl;
}

void TreeNode::printIndent(int indent, bool end, ostream& out) {
  for (int i = 0; i < indent; i++) {
    out << "│   ";
  }
  if (end)
    out << "└──";
  else
    out << "├──";
};


void TreeNode::printSpace(int indent, ostream& out)
{
    for (int i = 0; i < indent; i++)
        out << "  ";
}

/* CompUnit */
void NCompUnit::print(int indent, bool end, ostream& out)
{
    this->printIndent(indent, end, out);
    out << "CompUnit" << "\n";
    for (auto child = body.begin(); child != body.end(); child++)
        (*child)->print(indent+1, child+1 == body.end(), out);
}

/* Identifier */
NIdentifier::NIdentifier(string name) : name(name) { }

void NIdentifier::print(int indent, bool end, ostream& out)
{
    this->printIndent(indent, end, out);
    out << "Identifier: " << this->name << "\n";
}

/* ArrayIdentifier */
NArrayIdentifier::NArrayIdentifier(NIdentifier& ident) : NIdentifier(ident), ident(ident) { }

void NArrayIdentifier::print(int indent, bool end, ostream& out)
{
    this->printIndent(indent, end, out);
    out << "ArrayIdentifier" << "\n";
    ident.print(indent+1, false, out);

    this->printIndent(indent+1, true, out);
    out << "ArrayShape" << "\n";
    for (auto i = shape.begin(); i != shape.end(); i++)
        (*i)->print(indent+2, i+1 == shape.end(), out);
}

/* Number */
NNumber::NNumber(int value) : value(value) { }

NNumber::NNumber(const string& value) 
{ 
    this->value = stol(value, 0, 0);
}

void NNumber::print(int indent, bool end, ostream& out)
{
    this->printIndent(indent, end, out);
    out << "Number: " << this->value << "\n";
}

/* DeclareStmt */
NDeclareStmt::NDeclareStmt(int type) : type(type) { }

void NDeclareStmt::print(int indent, bool end, ostream& out)
{
    this->printIndent(indent, end, out);
    out << "DeclareStmt" << "\n";
    for (auto i = decl_list.begin(); i != decl_list.end(); i++)
        (*i)->print(indent+1, i+1 == decl_list.end(), out);
}

/* VarDeclare */
NVarDeclare::NVarDeclare(NIdentifier& ident) : ident(ident) {}

void NVarDeclare::print(int indent, bool end, ostream& out)
{
    this->printIndent(indent, end, out);
    out << "VarDeclare" << "\n";
    ident.print(indent+1, true, out);
}

/* VarDeclareWithInit */
NVarDeclareWithInit::NVarDeclareWithInit(NIdentifier& ident, NExpression& value, bool is_const) : ident(ident), value(value), is_const(is_const) { }

void NVarDeclareWithInit::print(int indent, bool end, ostream& out)
{
    this->printIndent(indent, end, out);
    out << "VarDeclareWithInit: is_const=" << is_const << "\n";
    ident.print(indent+1, end, out);
    value.print(indent+1, true, out);
}

/* ArrayDeclare */
NArrayDeclare::NArrayDeclare(NArrayIdentifier& ident) : ident(ident) { }

void NArrayDeclare::print(int indent, bool end, ostream& out)
{
    this->printIndent(indent, end, out);
    out << "ArrayDeclare" << "\n";
    ident.print(indent+1, true, out);
}

/* ArrayDeclareWithInit */
NArrayDeclareWithInit::NArrayDeclareWithInit(NArrayIdentifier& ident, NArrayDeclareInitValue& value, bool is_const) : ident(ident), value(value), is_const(is_const) { }

void NArrayDeclareWithInit::print(int indent, bool end, ostream& out)
{
    this->printIndent(indent, end, out);
    out << "ArrayDeclareWithInit: is_const=" << is_const << "\n";
    ident.print(indent+1, false, out);
    value.print(indent+1, true, out);
}

/* ArrayDeclareInitValue */
NArrayDeclareInitValue::NArrayDeclareInitValue(bool is_number, NExpression* value) : is_number(is_number), value(value) { }

void NArrayDeclareInitValue::print(int indent, bool end, ostream& out)
{
    this->printIndent(indent, end, out);
    out << "ArrayDeclareInitValue: is_number=" << is_number << "\n";
    if (is_number)
        value->print(indent+1, true, out);
    else
    {
        for (auto i = value_list.begin(); i != value_list.end(); i++)
            (*i)->print(indent+1, i+1 == value_list.end(), out);
    } 
}

/* BinaryExpression */
NBinaryExpr::NBinaryExpr(NExpression& lhs, int op, NExpression& rhs) : lhs(lhs), op(op), rhs(rhs) { }

void NBinaryExpr::print(int indent, bool end, ostream& out)
{
    this->printIndent(indent, end, out);
    out << "BinaryExpr: " << get_token_str(op) << "\n";
    lhs.print(indent+1, end, out);
    rhs.print(indent+1, true, out);
}

/* UnaryExpression */
NUnaryExpr::NUnaryExpr(int op, NExpression& rhs) : op(op), rhs(rhs) { }

void NUnaryExpr::print(int indent, bool end, ostream& out)
{
    this->printIndent(indent, end, out);
    out << "UnaryExpr: " << get_token_str(op) << "\n";
    rhs.print(indent+1, true, out);
}

/* ConditionalExpression */
NCondExpr::NCondExpr(NExpression& value) : value(value) { }

void NCondExpr::print(int indent, bool end, ostream& out)
{
    this->printIndent(indent, end, out);
    out << "CondExpr" << "\n";
    value.print(indent+1, true, out);
}


/* FuncCallArgs */
void NFuncCallArgs::print(int indent, bool end, ostream& out)
{
    this->printIndent(indent, end, out);
    out << "FuncCallArgs" << "\n";
    for (auto i = args.begin(); i != args.end(); i++)
        (*i)->print(indent+1, i+1 == args.end(), out);
}

/* FuncCall */
NFuncCall::NFuncCall(NIdentifier& ident, NFuncCallArgs& args) : ident(ident), args(args) { }

void NFuncCall::print(int indent, bool end, ostream& out)
{
    this->printIndent(indent, end, out);
    out << "FuncCall" << "\n";
    ident.print(indent+1, false, out);
    args.print(indent+1, true, out);
}

/* FuncDef */
NFuncDef::NFuncDef(int return_type, NIdentifier& ident, NFuncDefArgs& args, NBlock& body)
    : return_type(return_type), ident(ident), args(args), body(body) { }

void NFuncDef::print(int indent, bool end, ostream& out)
{
    this->printIndent(indent, end, out);
    out << "FuncDef: return_type=" << get_token_str(return_type) << "\n";
    ident.print(indent+1, false, out);
    args.print(indent+1, false, out);
    body.print(indent+1, true, out);
}

/* FuncDefArg */
NFuncDefArg::NFuncDefArg(int type, NIdentifier& ident, bool is_array) : type(type), ident(ident), is_array(is_array) { }

void NFuncDefArg::print(int indent, bool end, ostream& out)
{
    this->printIndent(indent, end, out);
    out << "FuncDefArg: type=" << get_token_str(type) << "\n";
    ident.print(indent+1, true, out);
}

/* FuncDefArgs */
void NFuncDefArgs::print(int indent, bool end, ostream& out)
{
    this->printIndent(indent, end, out);
    out << "FuncDefArgs" << "\n";
    for (auto i = args.begin(); i != args.end(); i++)
        (*i)->print(indent+1, i+1 == args.end(), out);
}

/* Block */
void NBlock::print(int indent, bool end, ostream& out)
{
    this->printIndent(indent, end, out);
    out << "Block" << "\n";
    for (auto i = body.begin(); i != body.end(); i++)
        (*i)->print(indent+1, i+1 == body.end(), out);
}

/* EvalStmt */
NEvalStmt::NEvalStmt(NExpression& value) : value(value) {}

void NEvalStmt::print(int indent, bool end, ostream& out)
{
    this->printIndent(indent, end, out);
    out << "EvalStmt" << "\n";
    value.print(indent+1, true, out);
}

/* VoidStmt */
void NVoidStmt::print(int indent, bool end, ostream& out)
{
    this->printIndent(indent, end, out);
    out << "VoidStmt" << "\n";
}

/* AssignStmt */
NAssignStmt::NAssignStmt(NIdentifier& lhs, NExpression& rhs) : lhs(lhs), rhs(rhs) { }

void NAssignStmt::print(int indent, bool end, ostream& out)
{
    this->printIndent(indent, end, out);
    out << "AssignStmt" << "\n";
    lhs.print(indent+1, false, out);
    rhs.print(indent+1, true, out);
}

/* IfStmt */
NIfStmt::NIfStmt(NCondExpr& cond, NStatement& then_stmt) : cond(cond), then_stmt(then_stmt) { }

void NIfStmt::print(int indent, bool end, ostream& out)
{
    this->printIndent(indent, end, out);
    out << "IfStmt" << "\n";

    this->printIndent(indent+1, false, out);
    out << "Condition" << "\n";
    cond.print(indent+1, false, out);

    this->printIndent(indent+1, false, out);
    out << "ThenStmt" << "\n";
    then_stmt.print(indent+1, true, out);
}

/* IfElseStmt */
NIfElseStmt::NIfElseStmt(NCondExpr& cond, NStatement& then_stmt, NStatement& else_stmt) : cond(cond), then_stmt(then_stmt), else_stmt(else_stmt) { }

void NIfElseStmt::print(int indent, bool end, ostream& out)
{
    this->printIndent(indent, end, out);
    out << "IfStmt" << "\n";

    this->printIndent(indent+1, false, out);
    out << "Condition" << "\n";
    cond.print(indent+1, false, out);

    this->printIndent(indent+1, false, out);
    out << "ThenStmt" << "\n";
    then_stmt.print(indent+1, false, out);

    this->printIndent(indent+1, false, out);
    out << "ElseStmt" << "\n";
    else_stmt.print(indent+1, true, out);
}

/* ReturnStmt */
NReturnStmt::NReturnStmt(NExpression* value) : value(value) { }

void NReturnStmt::print(int indent, bool end, ostream& out)
{
    this->printIndent(indent, end, out);
    out << "ReturnStmt" << "\n";
    if (value)
        value->print(indent+1, true, out);
}

/* WhileStmt */
NWhileStmt::NWhileStmt(NCondExpr& cond, NStatement& do_stmt) : cond(cond), do_stmt(do_stmt) { }

void NWhileStmt::print(int indent, bool end, ostream& out)
{
    this->printIndent(indent, end, out);
    out << "WhileStmt" << "\n";

    this->printIndent(indent+1, false, out);
    out << "Condition" << "\n";
    cond.print(indent+1, false, out);

    this->printIndent(indent+1, false, out);
    out << "DoStmt" << "\n";
    do_stmt.print(indent+1, true, out);
}

/* BreakStmt */
void NBreakStmt::print(int indent, bool end, ostream& out)
{
    this->printIndent(indent, end, out);
    out << "BreakStmt" << "\n";
}

/* ContinueStmt */
void NContinueStmt::print(int indent, bool end, ostream& out)
{
    this->printIndent(indent, end, out);
    out << "ContinueStmt" << "\n";
}