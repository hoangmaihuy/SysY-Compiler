#pragma once
#include "globals.hpp"
#include "symtab.hpp"

class TreeNode 
{
public:
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    void printIndent(int indent=0, bool end=false, ostream& out=cerr);
    void printSpace(int indent=0, ostream& out=cout);
    virtual void generate_eeyore(Context& ctx, int indent, ostream& out=cout);
};

class NCompUnit : public TreeNode
{
public:
    vector<TreeNode*> body;
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(Context& ctx, int indent, ostream& out=cout);
};

class NExpression : public TreeNode
{
public:
    string ee_name;
    virtual int eval(Context& ctx);
    virtual void generate_eeyore(Context& ctx, int indent, ostream& out=cout);
};

class NCondExpr : public NExpression
{
public:
    NExpression& value;
    NCondExpr(NExpression& value);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(Context& ctx, int indent, ostream& out=cout);
};

class NIdentifier : public NExpression
{
public:
    string name;
    NIdentifier(string name);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(Context& ctx, int indent, ostream& out=cout);
    virtual int eval(Context& ctx);
};

class NArrayIdentifier : public NIdentifier
{
public:
    NIdentifier& ident;
    vector<NExpression*> shape;
    NArrayIdentifier(NIdentifier& ident);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual int eval(Context& ctx);
    virtual vector<int> get_shape(Context& ctx);
    virtual void generate_eeyore(Context& ctx, int indent, ostream& out=cout);
};

class NNumber : public NExpression
{
public:
    int value;
    NNumber(const string& value);
    NNumber(int value);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(Context& ctx, int indent, ostream& out=cout);
    virtual int eval(Context& ctx);
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
    virtual void generate_eeyore(Context& ctx, int indent, ostream& out=cout);
};

class NVarDeclareWithInit : public NDeclare
{
public:
    NIdentifier& ident;
    NExpression& value;
    bool is_const;
    NVarDeclareWithInit(NIdentifier& ident, NExpression& value, bool is_const=false);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(Context& ctx, int indent, ostream& out=cout);
};

class NVarDeclare : public NDeclare
{
public:
    NIdentifier& ident;
    NVarDeclare(NIdentifier& ident);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(Context& ctx, int indent, ostream& out=cout);
};

class NArrayDeclareInitValue : public NExpression 
{
public:
    bool is_number;
    NExpression* value;
    vector<NExpression*> value_list;
    NArrayDeclareInitValue(bool is_number, NExpression* value);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void write_values(Context& ctx, int start_index, vector<int>& shape, vector<int>& init_values);
    virtual void generate_eeyore(Context& ctx, string ee_name, vector<int>& shape, int start_index, int indent, ostream& out);
};

class NArrayDeclareWithInit : public NDeclare
{
public:
    NArrayIdentifier& ident;
    NArrayDeclareInitValue& value;
    bool is_const;
    NArrayDeclareWithInit(NArrayIdentifier& ident, NArrayDeclareInitValue& value, bool is_const=false);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(Context& ctx, int indent, ostream& out=cout);
};

class NArrayDeclare : public NDeclare
{
public:
    NArrayIdentifier& ident;    
    NArrayDeclare(NArrayIdentifier& ident);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(Context& ctx, int indent, ostream& out=cout);
};

class NBinaryExpr : public NExpression
{
public:
    int op;
    NExpression& lhs;
    NExpression& rhs;
    NBinaryExpr(NExpression& lhs, int op, NExpression& rhs);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(Context& ctx, int indent, ostream& out=cout);
    virtual int eval(Context& ctx);
};

class NUnaryExpr : public NExpression
{
public:
    int op;
    NExpression& rhs;
    NUnaryExpr(int op, NExpression& rhs);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(Context& ctx, int indent, ostream& out=cout);
    virtual int eval(Context& ctx);
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
    virtual void generate_eeyore(Context& ctx, int indent, ostream& out=cout);
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
    virtual void generate_eeyore(Context& ctx, int indent, ostream& out=cout);
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
    virtual void generate_eeyore(Context& ctx, int indent, ostream& out=cout);
};


class NEvalStmt : public NStatement
{
public:
    NExpression& value;
    NEvalStmt(NExpression& value);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(Context& ctx, int indent, ostream& out=cout);
};

class NVoidStmt : public NStatement
{
public:
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(Context& ctx, int indent, ostream& out=cout);
};

class NAssignStmt : public NStatement
{
public:
    NIdentifier& lhs;
    NExpression& rhs;
    NAssignStmt(NIdentifier& lhs, NExpression& rhs);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(Context& ctx, int indent, ostream& out=cout);
};

class NIfStmt : public NStatement
{
public:
    NCondExpr& cond;
    NStatement& then_stmt;
    NIfStmt(NCondExpr& cond, NStatement& then_stmt);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(Context& ctx, int indent, ostream& out=cout);
};

class NIfElseStmt : public NStatement
{
public:
    NCondExpr& cond;
    NStatement& then_stmt;
    NStatement& else_stmt;
    NIfElseStmt(NCondExpr& cond, NStatement& then_stmt, NStatement& else_stmt);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(Context& ctx, int indent, ostream& out=cout);
};

class NReturnStmt : public NStatement
{
public:
    NExpression* value;
    NReturnStmt(NExpression* value = nullptr);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(Context& ctx, int indent, ostream& out=cout);
};

class NWhileStmt : public NStatement
{
public:
    NCondExpr& cond;
    NStatement& do_stmt;
    NWhileStmt(NCondExpr& cond, NStatement& do_stmt);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(Context& ctx, int indent, ostream& out=cout);
};

class NContinueStmt : public NStatement
{
public:
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(Context& ctx, int indent, ostream& out=cout);
};

class NBreakStmt : public NStatement
{
public:
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    virtual void generate_eeyore(Context& ctx, int indent, ostream& out=cout);
};