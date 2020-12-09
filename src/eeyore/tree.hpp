#pragma once
#include "globals.hpp"
#include "context_eeyore.hpp"

class TreeNode 
{
public:
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    void printIndent(int indent=0, bool end=false, ostream& out=cerr);
    void printSpace(int indent=0, ostream& out=cout);
    virtual void generate_eeyore(ContextEeyore& ctx, int indent);
};

class NCompUnit : public TreeNode
{
public:
    vector<TreeNode*> body;
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(ContextEeyore& ctx, int indent);
};

class NExpression : public TreeNode
{
public:
    EValue* e_value;
    virtual int eval(ContextEeyore& ctx);
    virtual void generate_eeyore(ContextEeyore& ctx, int indent);
};

class NCondExpr : public NExpression
{
public:
    NExpression& value;
    NCondExpr(NExpression& value);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(ContextEeyore& ctx, int indent);
};

class NIdentifier : public NExpression
{
public:
    string name;
    NIdentifier(string name);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(ContextEeyore& ctx, int indent);
    virtual void generate_eeyore(ContextEeyore& ctx, int indent, bool is_lhs=false);
    virtual int eval(ContextEeyore& ctx);
};

class NArrayIdentifier : public NIdentifier
{
public:
    NIdentifier& ident;
    vector<NExpression*> shape;
    NArrayIdentifier(NIdentifier& ident);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual int eval(ContextEeyore& ctx);
    virtual vector<int> get_shape(ContextEeyore& ctx);
    virtual void generate_eeyore(ContextEeyore& ctx, int indent);
    virtual void generate_eeyore(ContextEeyore& ctx, int indent, bool is_lhs=false);
};

class NNumber : public NExpression
{
public:
    long long value;
    NNumber(const string& value);
    NNumber(int value);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(ContextEeyore& ctx, int indent);
    virtual int eval(ContextEeyore& ctx);
};

class NStatement : public TreeNode 
{
};

class NDeclare : public TreeNode
{
};

class NDeclareStmt : public NStatement
{
public:
    int type;
    vector<NDeclare*> decl_list;

    NDeclareStmt(int type);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(ContextEeyore& ctx, int indent);
};

class NVarDeclareWithInit : public NDeclare
{
public:
    NIdentifier& ident;
    NExpression& value;
    bool is_const;
    NVarDeclareWithInit(NIdentifier& ident, NExpression& value, bool is_const=false);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(ContextEeyore& ctx, int indent);
};

class NVarDeclare : public NDeclare
{
public:
    NIdentifier& ident;
    NVarDeclare(NIdentifier& ident);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(ContextEeyore& ctx, int indent);
};

class NArrayDeclareInitValue : public NExpression 
{
public:
    bool is_number;
    NExpression* value;
    vector<NExpression*> value_list;
    NArrayDeclareInitValue(bool is_number, NExpression* value);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void write_values(ContextEeyore& ctx, int start_index, vector<int>& shape, vector<int>& init_values);
    virtual void generate_eeyore(ContextEeyore& ctx, EVariable* ee_var, vector<int>& shape, int start_index, int indent);
};

class NArrayDeclareWithInit : public NDeclare
{
public:
    NArrayIdentifier& ident;
    NArrayDeclareInitValue& value;
    bool is_const;
    NArrayDeclareWithInit(NArrayIdentifier& ident, NArrayDeclareInitValue& value, bool is_const=false);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(ContextEeyore& ctx, int indent);
};

class NArrayDeclare : public NDeclare
{
public:
    NArrayIdentifier& ident;    
    NArrayDeclare(NArrayIdentifier& ident);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(ContextEeyore& ctx, int indent);
};

class NBinaryExpr : public NExpression
{
public:
    int op;
    NExpression& lhs;
    NExpression& rhs;
    NBinaryExpr(NExpression& lhs, int op, NExpression& rhs);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(ContextEeyore& ctx, int indent);
    virtual int eval(ContextEeyore& ctx);
};

class NUnaryExpr : public NExpression
{
public:
    int op;
    NExpression& rhs;
    NUnaryExpr(int op, NExpression& rhs);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(ContextEeyore& ctx, int indent);
    virtual int eval(ContextEeyore& ctx);
};

class NFuncCallArgs : public TreeNode
{
public:
    vector<NExpression*> args;
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
};

class NFuncCall : public NExpression
{
public:
    NIdentifier& ident;
    NFuncCallArgs& args;
    NFuncCall(NIdentifier& ident, NFuncCallArgs& args);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(ContextEeyore& ctx, int indent);
};

class NFuncDefArg : public NExpression
{
public:
    int type;
    NIdentifier& ident;
    bool is_array;
    NFuncDefArg(int type, NIdentifier& ident, bool is_array=false);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
};

class NFuncDefArgs : public NExpression
{
public:
    vector<NFuncDefArg*> args;
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
};

class NBlock : public TreeNode
{
public:
    vector<NStatement*> body;
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(ContextEeyore& ctx, int indent);
};

class NFuncDef : public TreeNode
{
public:
    int return_type;
    NIdentifier& ident;
    NFuncDefArgs& args;
    NBlock& body;
    NFuncDef(int return_type, NIdentifier& ident, NFuncDefArgs& args, NBlock& body);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(ContextEeyore& ctx, int indent);
};


class NEvalStmt : public NStatement
{
public:
    NExpression& value;
    NEvalStmt(NExpression& value);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(ContextEeyore& ctx, int indent);
};

class NVoidStmt : public NStatement
{
public:
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(ContextEeyore& ctx, int indent);
};

class NAssignStmt : public NStatement
{
public:
    NIdentifier& lhs;
    NExpression& rhs;
    NAssignStmt(NIdentifier& lhs, NExpression& rhs);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(ContextEeyore& ctx, int indent);
};

class NIfStmt : public NStatement
{
public:
    NCondExpr& cond;
    NStatement& then_stmt;
    NIfStmt(NCondExpr& cond, NStatement& then_stmt);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(ContextEeyore& ctx, int indent);
};

class NIfElseStmt : public NStatement
{
public:
    NCondExpr& cond;
    NStatement& then_stmt;
    NStatement& else_stmt;
    NIfElseStmt(NCondExpr& cond, NStatement& then_stmt, NStatement& else_stmt);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(ContextEeyore& ctx, int indent);
};

class NReturnStmt : public NStatement
{
public:
    NExpression* value;
    NReturnStmt(NExpression* value = nullptr);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(ContextEeyore& ctx, int indent);
};

class NWhileStmt : public NStatement
{
public:
    NCondExpr& cond;
    NStatement& do_stmt;
    NWhileStmt(NCondExpr& cond, NStatement& do_stmt);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(ContextEeyore& ctx, int indent);
};

class NContinueStmt : public NStatement
{
public:
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(ContextEeyore& ctx, int indent);
};

class NBreakStmt : public NStatement
{
public:
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(ContextEeyore& ctx, int indent);
};