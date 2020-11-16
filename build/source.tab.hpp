/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_HOME_MEW_GIT_SYSY_CPP_BUILD_SOURCE_TAB_HPP_INCLUDED
# define YY_YY_HOME_MEW_GIT_SYSY_CPP_BUILD_SOURCE_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INTEGER = 258,
    IDENTIFIER = 259,
    IF = 260,
    ELSE = 261,
    WHILE = 262,
    BREAK = 263,
    CONTINUE = 264,
    RETURN = 265,
    CONST = 266,
    INT = 267,
    VOID = 268,
    ASSIGN = 269,
    EQ = 270,
    NE = 271,
    LT = 272,
    LE = 273,
    GT = 274,
    GE = 275,
    AND = 276,
    OR = 277,
    L_PAREN = 278,
    R_PAREN = 279,
    L_BRACE = 280,
    R_BRACE = 281,
    L_SQUARE = 282,
    R_SQUARE = 283,
    COMMA = 284,
    SEMI = 285,
    PLUS = 286,
    MINUS = 287,
    MUL = 288,
    DIV = 289,
    MOD = 290,
    NOT = 291
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 17 "src/sysy2eeyore/sysy.y"

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

#line 113 "/home/mew/Git/SysY-Cpp/build/source.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_HOME_MEW_GIT_SYSY_CPP_BUILD_SOURCE_TAB_HPP_INCLUDED  */
