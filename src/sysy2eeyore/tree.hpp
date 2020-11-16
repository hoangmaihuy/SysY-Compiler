#include "globals.hpp"

class TreeNode 
{
public:
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
    void printIndent(int indent=0, bool end=false, ostream& out=cerr);
};

class NCompUnit : public TreeNode
{
public:
    vector<TreeNode*> body;
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
};

class NExpression : public TreeNode
{
};

class NCondExpr : public NExpression
{
public:
    NExpression& value;
    NCondExpr(NExpression& value);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
};

class NIdentifier : public TreeNode
{
public:
    string name;
    NIdentifier(string name);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
};

class NArrayIdentifier : public NIdentifier
{
public:
    NIdentifier& ident;
    vector<NExpression*> shape;
    NArrayIdentifier(NIdentifier& ident);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
};

class NNumber : public NExpression
{
public:
    int value;
    NNumber(const string& value);
    NNumber(int value);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
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
};

class NVarDeclareWithInit : public NDeclare
{
public:
    NIdentifier& ident;
    NExpression& value;
    bool is_const;
    NVarDeclareWithInit(NIdentifier& ident, NExpression& value, bool is_const=false);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
};

class NVarDeclare : public NDeclare
{
public:
    NIdentifier& ident;
    NVarDeclare(NIdentifier& ident);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
};

class NArrayDeclareInitValue : public NExpression 
{
public:
    bool is_number;
    NExpression* value;
    vector<NExpression*> value_list;
    NArrayDeclareInitValue(bool is_number, NExpression* value);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
};

class NArrayDeclareWithInit : public NDeclare
{
public:
    NArrayIdentifier& ident;
    NArrayDeclareInitValue& value;
    bool is_const;
    NArrayDeclareWithInit(NArrayIdentifier& ident, NArrayDeclareInitValue& value, bool is_const=false);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
};

class NArrayDeclare : public NDeclare
{
public:
    NArrayIdentifier& ident;    
    NArrayDeclare(NArrayIdentifier& ident);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
};

class NBinaryExpr : public NExpression
{
public:
    int op;
    NExpression& lhs;
    NExpression& rhs;
    NBinaryExpr(NExpression& lhs, int op, NExpression& rhs);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
};

class NUnaryExpr : public NExpression
{
public:
    int op;
    NExpression& rhs;
    NUnaryExpr(int op, NExpression& rhs);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
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
};

class NFuncDefArg : public NExpression
{
public:
    int type;
    NIdentifier& ident;
    NFuncDefArg(int type, NIdentifier& ident);
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
};


class NEvalStmt : public NStatement
{
public:
    NExpression& value;
    NEvalStmt(NExpression& value);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
};

class NVoidStmt : public NStatement
{
public:
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
};

class NAssignStmt : public NStatement
{
public:
    NIdentifier& lhs;
    NExpression& rhs;
    NAssignStmt(NIdentifier& lhs, NExpression& rhs);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
};

class NIfStmt : public NStatement
{
public:
    NCondExpr& cond;
    NStatement& then_stmt;
    NIfStmt(NCondExpr& cond, NStatement& then_stmt);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
};

class NIfElseStmt : public NStatement
{
public:
    NCondExpr& cond;
    NStatement& then_stmt;
    NStatement& else_stmt;
    NIfElseStmt(NCondExpr& cond, NStatement& then_stmt, NStatement& else_stmt);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
};

class NReturnStmt : public NStatement
{
public:
    NExpression* value;
    NReturnStmt(NExpression* value = nullptr);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
};

class NWhileStmt : public NStatement
{
public:
    NCondExpr& cond;
    NStatement& do_stmt;
    NWhileStmt(NCondExpr& cond, NStatement& do_stmt);
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
};

class NContinueStmt : public NStatement
{
public:
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
};

class NBreakStmt : public NStatement
{
public:
    virtual void print(int indent=0, bool end=false, ostream& out=cerr);
};