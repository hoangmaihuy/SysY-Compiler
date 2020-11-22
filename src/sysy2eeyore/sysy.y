%{
#include "globals.hpp"
#include "tree.hpp"

extern int yylex();
extern int yyget_lineno();
extern int yydebug;

void yyerror(const char *s) { std::printf("Error(line: %d): %s\n", yyget_lineno(), s); if (!yydebug) std::exit(1); }
#define YYERROR_VERBOSE true
#define YYDEBUG 1

NCompUnit* root;

%}

%union {
    int token;
    NCompUnit* comp_unit;
    NIdentifier* ident;
    NDeclare* decl;
    NFuncDef* func_def;
    NExpression* expr;
    NDeclareStmt* decl_stmt;
    NArrayIdentifier* array_ident;
    NCondExpr* cond_expr;
    NStatement* stmt;
    NBlock* block;
    NArrayDeclareInitValue* array_init_val;
    NFuncDefArg* func_def_arg;
    NFuncDefArgs* func_def_args;
    NFuncCallArgs* func_call_args;
    std::string* string;
}

%token <string> INTEGER IDENTIFIER
%token <token> IF ELSE WHILE BREAK CONTINUE RETURN
%token <token> CONST INT VOID
%token <token> ASSIGN EQ NE LT LE GT GE
%token <token> AND OR
%token <token> L_PAREN R_PAREN L_BRACE R_BRACE L_SQUARE R_SQUARE

%token <token> COMMA SEMI
%token <token> PLUS MINUS MUL DIV MOD NOT

%type <token> AddOp MulOp RelOp UnaryOp BType
%type <ident> Ident LVal
%type <expr> Number Exp InitVal LOrExp LAndExp EqExp AddExp MulExp PrimaryExp RelExp UnaryExp FuncCall
%type <comp_unit> CompUnit
%type <decl_stmt> Decl ConstDecl VarDecl ConstDeclStmt VarDeclStmt
%type <decl> VarDef VarDefOne VarDefArray ConstDef ConstDefOne ConstDefArray
%type <array_ident> DefArrayName ArrayItem
%type <func_def> FuncDef
%type <func_def_args> FuncFParams
%type <func_def_arg> FuncFParam FuncFParamArray FuncFParamOne
%type <array_init_val> InitValArray InitValArrayIn
%type <func_call_args> FuncRParams
%type <block> Block BlockItems
%type <stmt> BlockItem Stmt AssignStmt AssignStmtNoSemi IfStmt ReturnStmt WhileStmt BreakStmt ContinueStmt
%type <cond_expr> Cond

%start CompUnit
%%

CompUnit        : CompUnit Decl { $$ = $1; $$->body.push_back($<decl>2); }
                | CompUnit FuncDef { $$ = $1; $$->body.push_back($<func_def>2); }
                | Decl { $$ = new NCompUnit(); root = $$; $$->body.push_back($<decl>1); }
                | FuncDef { $$ = new NCompUnit(); root = $$; $$->body.push_back($<func_def>1); }
                ;

Decl            : ConstDeclStmt
                | VarDeclStmt
                ;

BType           : INT
                ;

ConstDeclStmt   : ConstDecl SEMI { $$ = $1; }
                ;

ConstDecl       : CONST BType ConstDef { $$ = new NDeclareStmt($2); $$->decl_list.push_back($3); }
                | ConstDecl COMMA ConstDef { $$ = $1; $$->decl_list.push_back($3); }
                ;

ConstDef        : ConstDefOne
                | ConstDefArray
                ;

ConstDefOne     : Ident ASSIGN InitVal { $$ = new NVarDeclareWithInit(*$1, *$3, true); }
                ;

ConstDefArray   : DefArrayName ASSIGN InitValArray { $$ = new NArrayDeclareWithInit(*$1, *$3, true); }
                ;


VarDeclStmt     : VarDecl SEMI { $$ = $1; }
                ;

VarDecl         : BType VarDef { $$ = new NDeclareStmt($1); $$->decl_list.push_back($2); }
                | VarDecl COMMA VarDef { $$ = $1; $$->decl_list.push_back($3); }
                ;

VarDef          : VarDefOne
                | VarDefArray
                ;

VarDefOne       : Ident ASSIGN InitVal { $$ = new NVarDeclareWithInit(*$1, *$3, false); }
                | Ident { $$ = new NVarDeclare(*$1); }
                ;

VarDefArray     : DefArrayName ASSIGN InitValArray { $$ = new NArrayDeclareWithInit(*$1, *$3, false); } 
                | DefArrayName { $$ = new NArrayDeclare(*$1); }
                ;

DefArrayName    : DefArrayName L_SQUARE Exp R_SQUARE { $$ = $1; $$->shape.push_back($3); }
                | Ident L_SQUARE Exp R_SQUARE { $$ = new NArrayIdentifier(*$1); $$->shape.push_back($3); }
                ;

InitVal         : AddExp
                ;

InitValArray    : L_BRACE InitValArrayIn R_BRACE { $$ = $2; }
                | L_BRACE R_BRACE { $$ = new NArrayDeclareInitValue(false, nullptr); }
                ;

InitValArrayIn  : InitValArrayIn COMMA InitValArray { $$ = $1; $$->value_list.push_back($3); }
                | InitValArrayIn COMMA InitVal { $$ = $1; $$->value_list.push_back(new NArrayDeclareInitValue(true, $3)); }
                | InitValArray { 
                    $$ = new NArrayDeclareInitValue(false, nullptr);
                    $$->value_list.push_back($1);
                }
                | InitVal {
                    $$ = new NArrayDeclareInitValue(false, nullptr);
                    $$->value_list.push_back(new NArrayDeclareInitValue(true, $1));
                }
                ;
                
Exp             : AddExp
                ;


LOrExp          : LAndExp OR LAndExp { $$ = new NBinaryExpr(*$1, $2, *$3); }
                | LOrExp OR LOrExp { $$ = new NBinaryExpr(*$1, $2, *$3); }
                | LAndExp
                ;

LAndExp         : LAndExp AND LAndExp { $$ = new NBinaryExpr(*$1, $2, *$3); }
                | EqExp
                ;

EqExp           : RelExp EQ RelExp { $$ = new NBinaryExpr(*$1, $2, *$3); }
                | RelExp NE RelExp { $$ = new NBinaryExpr(*$1, $2, *$3); }
                | RelExp
                ;

RelExp          : AddExp
                | RelExp RelOp AddExp { $$ = new NBinaryExpr(*$1, $2, *$3); }
                ;

AddExp          : AddExp AddOp MulExp { $$ = new NBinaryExpr(*$1, $2, *$3); }
                | MulExp
                ;

MulExp          : MulExp MulOp UnaryExp { $$ = new NBinaryExpr(*$1, $2, *$3); }
                | UnaryExp
                ;

UnaryExp        : UnaryOp UnaryExp { $$ = new NUnaryExpr($1, *$2); }
                | FuncCall
                | PrimaryExp
                ;

FuncCall        : Ident L_PAREN FuncRParams R_PAREN { $$ = new NFuncCall(*$1, *$3);  }
                | Ident L_PAREN R_PAREN { $$ = new NFuncCall(*$1, *(new NFuncCallArgs())); }
                ;

FuncRParams     : FuncRParams COMMA AddExp { $$ = $1; $$->args.push_back($3); }
                | AddExp { $$ = new NFuncCallArgs(); $$->args.push_back($1); }
                ;

PrimaryExp      : LVal
                | Number
                | L_PAREN Exp R_PAREN { $$ = $2; }
                | AssignStmtNoSemi
                ;

ArrayItem       : LVal L_SQUARE Exp R_SQUARE { $$ = new NArrayIdentifier(*$1); $$->shape.push_back($3); }
                | ArrayItem L_SQUARE Exp R_SQUARE { $$ = $1; $$->shape.push_back($3); }
                ;

LVal            : ArrayItem
                | Ident
                ;

FuncDef         : BType Ident L_PAREN FuncFParams R_PAREN Block { $$ = new NFuncDef($1, *$2, *$4, *$6); }
                | BType Ident L_PAREN R_PAREN Block { $$ = new NFuncDef($1, *$2, *(new NFuncDefArgs()), *$5); }
                | VOID Ident L_PAREN FuncFParams R_PAREN Block { $$ = new NFuncDef($1, *$2, *$4, *$6); }
                | VOID Ident L_PAREN R_PAREN Block { $$ = new NFuncDef($1, *$2, *(new NFuncDefArgs()), *$5); }
                ;

FuncFParams     : FuncFParams COMMA FuncFParam { $$ = $1; $$->args.push_back($3); }
                | FuncFParam { $$ = new NFuncDefArgs(); $$->args.push_back($1); }
                ;

FuncFParam      : FuncFParamOne
                | FuncFParamArray
                ;

FuncFParamOne   : BType Ident { $$ = new NFuncDefArg($1, *$2); }
                ;

FuncFParamArray : FuncFParamOne L_SQUARE R_SQUARE { 
                    auto ident = new NIdentifier($1->ident.name);
                    auto array_ident = new NArrayIdentifier(*ident);
                    array_ident->shape.push_back(new NNumber(1));
                    $$ = new NFuncDefArg($1->type, *array_ident, true);
                }
                | FuncFParamArray L_SQUARE Exp R_SQUARE {  
                    $$ = $1;
                    NArrayIdentifier& array_ident = (NArrayIdentifier&)$$->ident;
                    array_ident.shape.push_back($3);
                } 
                ;

Block           : L_BRACE R_BRACE { $$ = new NBlock(); }
                | L_BRACE BlockItems R_BRACE { $$ = $2; }
                ;

BlockItems      : BlockItem { $$ = new NBlock(); $$->body.push_back($1); }
                | BlockItems BlockItem { $$ = $1; $$->body.push_back($2); }
                ;

BlockItem       : Decl
                | Stmt
                ;

Stmt            : Block
                | AssignStmt
                | IfStmt
                | ReturnStmt
                | WhileStmt
                | BreakStmt
                | ContinueStmt
                | Exp SEMI { $$ = new NEvalStmt(*$1); }
                | SEMI { $$ = new NVoidStmt(); }
                ;

AssignStmt      : AssignStmtNoSemi SEMI { $$ = $1; }
                ;

AssignStmtNoSemi: LVal ASSIGN AddExp { $$ = new NAssignStmt(*$1, *$3); }
                ;

IfStmt          : IF L_PAREN Cond R_PAREN Stmt { $$ = new NIfStmt(*$3, *$5); }
                | IF L_PAREN Cond R_PAREN Stmt ELSE Stmt { $$ = new NIfElseStmt(*$3, *$5, *$7); }
                ;

ReturnStmt      : RETURN Exp SEMI { $$ = new NReturnStmt($2); }
                | RETURN SEMI { $$ = new NReturnStmt(); }
                ;

WhileStmt       : WHILE L_PAREN Cond R_PAREN Stmt { $$ = new NWhileStmt(*$3, *$5); }
                ;

BreakStmt       : BREAK SEMI { $$ = new NBreakStmt(); }
                ;

ContinueStmt    : CONTINUE SEMI { $$ = new NContinueStmt(); }
                ;

Cond            : LOrExp
                ;

Number          : INTEGER { $$ = new NNumber(*$1); }
                ;

AddOp           : PLUS
                | MINUS
                ;

MulOp           : MUL
                | DIV
                | MOD
                ;

UnaryOp         : PLUS
                | MINUS
                | NOT
                ;

RelOp           : GT
                | GE
                | LT
                | LE
                ;

Ident           : IDENTIFIER { $$ = new NIdentifier(*$1); }
                ;

%%

NCompUnit* parse()
{
    yyparse();
    return root;
}