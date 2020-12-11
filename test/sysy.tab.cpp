/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/eeyore/sysy.y"

#include "globals.hpp"
#include "sysy_tree.hpp"

extern int yylex();
extern int yyget_lineno();
extern int yydebug;

void yyerror(const char *s) { std::printf("Error(line: %d): %s\n", yyget_lineno(), s); if (!yydebug) std::exit(1); }
#define YYERROR_VERBOSE true
#define YYDEBUG 1

NCompUnit* root;


#line 86 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_HOME_MEW_GIT_SYSY_COMPILER_TEST_SYSY_TAB_HPP_INCLUDED
# define YY_YY_HOME_MEW_GIT_SYSY_COMPILER_TEST_SYSY_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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
#line 19 "src/eeyore/sysy.y"

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

#line 194 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_HOME_MEW_GIT_SYSY_COMPILER_TEST_SYSY_TAB_HPP_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   229

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  54
/* YYNRULES -- Number of rules.  */
#define YYNRULES  112
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  186

#define YYUNDEFTOK  2
#define YYMAXUTOK   291


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    67,    67,    68,    69,    70,    73,    74,    77,    80,
      83,    84,    87,    88,    91,    94,    98,   101,   102,   105,
     106,   109,   110,   113,   114,   117,   118,   121,   124,   125,
     128,   129,   130,   134,   140,   144,   145,   148,   149,   152,
     153,   154,   157,   158,   161,   162,   165,   166,   169,   170,
     171,   174,   175,   178,   179,   182,   183,   184,   185,   188,
     189,   192,   193,   196,   197,   198,   199,   202,   203,   206,
     207,   210,   213,   219,   226,   227,   230,   231,   234,   235,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   249,
     252,   255,   256,   259,   260,   263,   266,   269,   272,   275,
     278,   279,   282,   283,   284,   287,   288,   289,   292,   293,
     294,   295,   298
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "IDENTIFIER", "IF", "ELSE",
  "WHILE", "BREAK", "CONTINUE", "RETURN", "CONST", "INT", "VOID", "ASSIGN",
  "EQ", "NE", "LT", "LE", "GT", "GE", "AND", "OR", "L_PAREN", "R_PAREN",
  "L_BRACE", "R_BRACE", "L_SQUARE", "R_SQUARE", "COMMA", "SEMI", "PLUS",
  "MINUS", "MUL", "DIV", "MOD", "NOT", "$accept", "CompUnit", "Decl",
  "BType", "ConstDeclStmt", "ConstDecl", "ConstDef", "ConstDefOne",
  "ConstDefArray", "VarDeclStmt", "VarDecl", "VarDef", "VarDefOne",
  "VarDefArray", "DefArrayName", "InitVal", "InitValArray",
  "InitValArrayIn", "Exp", "LOrExp", "LAndExp", "EqExp", "RelExp",
  "AddExp", "MulExp", "UnaryExp", "FuncCall", "FuncRParams", "PrimaryExp",
  "ArrayItem", "LVal", "FuncDef", "FuncFParams", "FuncFParam",
  "FuncFParamOne", "FuncFParamArray", "Block", "BlockItems", "BlockItem",
  "Stmt", "AssignStmt", "AssignStmtNoSemi", "IfStmt", "ReturnStmt",
  "WhileStmt", "BreakStmt", "ContinueStmt", "Cond", "Number", "AddOp",
  "MulOp", "UnaryOp", "RelOp", "Ident", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291
};
# endif

#define YYPACT_NINF (-58)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     161,    12,   -58,    63,    28,   -58,    63,   -58,    77,   -58,
      83,   -58,    63,   -58,    62,   -58,   -58,   -58,   -58,   -58,
     -58,     8,    23,    63,   -58,    63,   -58,   -58,   -58,   -58,
      24,    29,    49,    72,   162,   162,    59,   162,   -58,   -58,
      43,    72,   162,    90,    63,    -9,   -58,   104,   117,    56,
     -58,   -58,   162,   -58,   -58,   -58,   111,   151,   143,   -58,
     -58,   -58,   120,    51,   -58,   -58,   162,   126,   -58,   151,
      90,    39,   124,   -58,   -58,    22,   -58,   -58,    90,    12,
     140,   162,   -58,   -58,   -58,   112,   158,   163,   -58,   184,
     151,   165,   -58,   -58,   -58,   162,   -58,   -58,   -58,   162,
     162,   162,   162,   -58,   122,   -58,    90,   -58,   174,   186,
     180,   181,   139,   -58,   -58,   -58,    63,   182,   -58,   125,
     -58,   -58,   -58,   183,   -58,   -58,   -58,   -58,   -58,   -58,
     -58,   -58,   187,   -58,   156,   162,   162,   162,   162,   -58,
     -58,   -58,   -58,   162,   -58,   143,   -58,   189,   151,   190,
     -58,   151,    81,   -58,   162,   162,   -58,   -58,   -58,   191,
     -58,   -58,   -58,   -58,   -58,   -58,   -58,   163,   -58,   188,
     188,   151,   -58,   -58,   -58,   162,   192,   195,   -58,   151,
      86,    86,   208,   -58,    86,   -58
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     8,     0,     0,     4,     0,     6,     0,     7,
       0,     5,     0,   112,     0,     1,     2,     3,    17,    19,
      20,    24,    22,     0,     9,     0,    16,    10,    12,    13,
       0,     0,     0,     0,     0,     0,     0,     0,    11,    18,
      22,     0,     0,     0,     0,     0,    68,    69,    70,     0,
      23,    99,     0,   105,   106,   107,     0,    34,    45,    47,
      49,    50,    61,    55,    58,    56,     0,    62,    21,    27,
       0,     0,     0,    15,    14,     0,    66,    71,     0,     0,
       0,     0,    29,    33,    32,     0,    98,    36,    38,    41,
      42,     0,    25,   100,   101,     0,   102,   103,   104,     0,
       0,     0,     0,    48,     0,    64,     0,    26,     0,     0,
       0,     0,     0,    74,    88,    78,     0,     0,    80,     0,
      76,    79,    81,    58,    82,    83,    84,    85,    86,    65,
      67,    72,     0,    28,     0,     0,     0,     0,     0,   110,
     111,   108,   109,     0,    57,    44,    46,     0,    90,     0,
      52,    54,     0,    63,     0,     0,    96,    97,    94,     0,
      87,    75,    77,    89,    73,    31,    30,    35,    37,    39,
      40,    43,    60,    59,    51,     0,     0,     0,    93,    53,
       0,     0,    91,    95,     0,    92
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -58,   -58,    80,     2,   -58,   -58,   197,   -58,   -58,   -58,
     -58,   198,   -58,   -58,    52,   -30,   -36,   -58,   -26,   -58,
      87,    50,    53,   -35,   129,   -50,   -58,   -58,   -58,   -58,
     -58,   221,   193,   147,   -58,   -58,   -34,   -58,   108,   -17,
     -58,   -57,   -58,   -58,   -58,   -58,   -58,    41,   -58,   -58,
     -58,   -58,   -58,    -2
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,   115,    44,     7,     8,    27,    28,    29,     9,
      10,    18,    19,    20,    21,    68,    50,    85,   117,    86,
      87,    88,    89,    57,    58,    59,    60,   152,    61,    62,
      63,    11,    45,    46,    47,    48,   118,   119,   120,   121,
     122,    64,   124,   125,   126,   127,   128,    91,    65,    95,
      99,    66,   143,    67
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      69,    14,     6,    12,    22,    73,     6,    69,    56,    76,
      31,    72,    74,    84,    69,    78,   103,    90,   123,    83,
      79,    31,    33,    40,     2,    51,    13,   108,    15,   109,
     110,   111,   112,     1,     2,    34,   105,    35,    41,     1,
       2,     3,    77,    42,   129,    52,    36,    75,   113,   146,
      37,    34,   114,    53,    54,   132,    37,    35,    55,    51,
      13,     2,   123,   106,    30,   101,   148,    13,    79,   151,
      37,     2,   153,    43,   147,    30,   149,   116,   102,    52,
       5,    49,    82,    70,    16,    32,   159,    53,    54,    51,
      13,   108,    55,   109,   110,   111,   112,    49,   166,    69,
      90,    90,    90,    90,   165,   174,    23,    24,   171,    52,
     175,    75,    25,    26,    40,    75,   114,    53,    54,    90,
      90,   116,    55,   123,   123,    51,    13,   123,    51,    13,
     108,    80,   109,   110,   111,   112,     1,     2,   133,    92,
     179,   134,    51,    13,    81,    52,   150,   100,    52,   104,
      75,   161,   107,    53,    54,   114,    53,    54,    55,    51,
      13,    55,    52,   182,   183,    51,    13,   185,   131,   158,
      53,    54,     1,     2,     3,    55,    96,    97,    98,    52,
     135,    49,    93,    94,   136,    52,   168,    53,    54,   144,
     169,   170,    55,    53,    54,   176,   177,   154,    55,   137,
     138,   139,   140,   141,   142,   139,   140,   141,   142,   155,
     156,   157,   160,   163,   184,   164,   180,   172,   173,   181,
      38,   178,   167,    39,   145,    17,   130,   162,     0,    71
};

static const yytype_int16 yycheck[] =
{
      35,     3,     0,     1,     6,    41,     4,    42,    34,    43,
      12,    37,    42,    49,    49,    24,    66,    52,    75,    49,
      29,    23,    14,    25,    12,     3,     4,     5,     0,     7,
       8,     9,    10,    11,    12,    27,    70,    14,    14,    11,
      12,    13,    44,    14,    78,    23,    23,    25,    26,    99,
      27,    27,    30,    31,    32,    81,    27,    14,    36,     3,
       4,    12,   119,    24,    12,    14,   101,     4,    29,   104,
      27,    12,   106,    24,   100,    23,   102,    75,    27,    23,
       0,    25,    26,    24,     4,    23,   112,    31,    32,     3,
       4,     5,    36,     7,     8,     9,    10,    25,   134,   134,
     135,   136,   137,   138,   134,    24,    29,    30,   143,    23,
      29,    25,    29,    30,   116,    25,    30,    31,    32,   154,
     155,   119,    36,   180,   181,     3,     4,   184,     3,     4,
       5,    27,     7,     8,     9,    10,    11,    12,    26,    28,
     175,    29,     3,     4,    27,    23,    24,    27,    23,    23,
      25,    26,    28,    31,    32,    30,    31,    32,    36,     3,
       4,    36,    23,   180,   181,     3,     4,   184,    28,    30,
      31,    32,    11,    12,    13,    36,    33,    34,    35,    23,
      22,    25,    31,    32,    21,    23,   136,    31,    32,    24,
     137,   138,    36,    31,    32,   154,   155,    23,    36,    15,
      16,    17,    18,    19,    20,    17,    18,    19,    20,    23,
      30,    30,    30,    30,     6,    28,    24,    28,    28,    24,
      23,    30,   135,    25,    95,     4,    79,   119,    -1,    36
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    11,    12,    13,    38,    39,    40,    41,    42,    46,
      47,    68,    40,     4,    90,     0,    39,    68,    48,    49,
      50,    51,    90,    29,    30,    29,    30,    43,    44,    45,
      51,    90,    23,    14,    27,    14,    23,    27,    43,    48,
      90,    14,    14,    24,    40,    69,    70,    71,    72,    25,
      53,     3,    23,    31,    32,    36,    55,    60,    61,    62,
      63,    65,    66,    67,    78,    85,    88,    90,    52,    60,
      24,    69,    55,    53,    52,    25,    73,    90,    24,    29,
      27,    27,    26,    52,    53,    54,    56,    57,    58,    59,
      60,    84,    28,    31,    32,    86,    33,    34,    35,    87,
      27,    14,    27,    62,    23,    73,    24,    28,     5,     7,
       8,     9,    10,    26,    30,    39,    40,    55,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    73,
      70,    28,    55,    26,    29,    22,    21,    15,    16,    17,
      18,    19,    20,    89,    24,    61,    62,    55,    60,    55,
      24,    60,    64,    73,    23,    23,    30,    30,    30,    55,
      30,    26,    75,    30,    28,    52,    53,    57,    58,    59,
      59,    60,    28,    28,    24,    29,    84,    84,    30,    60,
      24,    24,    76,    76,     6,    76
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    37,    38,    38,    38,    38,    39,    39,    40,    41,
      42,    42,    43,    43,    44,    45,    46,    47,    47,    48,
      48,    49,    49,    50,    50,    51,    51,    52,    53,    53,
      54,    54,    54,    54,    55,    56,    56,    57,    57,    58,
      58,    58,    59,    59,    60,    60,    61,    61,    62,    62,
      62,    63,    63,    64,    64,    65,    65,    65,    65,    66,
      66,    67,    67,    68,    68,    68,    68,    69,    69,    70,
      70,    71,    72,    72,    73,    73,    74,    74,    75,    75,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    77,
      78,    79,    79,    80,    80,    81,    82,    83,    84,    85,
      86,    86,    87,    87,    87,    88,    88,    88,    89,    89,
      89,    89,    90
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     1,     1,     1,     1,     1,     2,
       3,     3,     1,     1,     3,     3,     2,     2,     3,     1,
       1,     3,     1,     3,     1,     4,     4,     1,     3,     2,
       3,     3,     1,     1,     1,     3,     1,     3,     1,     3,
       3,     1,     1,     3,     3,     1,     3,     1,     2,     1,
       1,     4,     3,     3,     1,     1,     1,     3,     1,     4,
       4,     1,     1,     6,     5,     6,     5,     3,     1,     1,
       1,     2,     3,     4,     2,     3,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     2,
       3,     5,     7,     3,     2,     5,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 67 "src/eeyore/sysy.y"
                                { (yyval.comp_unit) = (yyvsp[-1].comp_unit); (yyval.comp_unit)->body.push_back((yyvsp[0].decl)); }
#line 1517 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 3:
#line 68 "src/eeyore/sysy.y"
                                   { (yyval.comp_unit) = (yyvsp[-1].comp_unit); (yyval.comp_unit)->body.push_back((yyvsp[0].func_def)); }
#line 1523 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 4:
#line 69 "src/eeyore/sysy.y"
                       { (yyval.comp_unit) = new NCompUnit(); root = (yyval.comp_unit); (yyval.comp_unit)->body.push_back((yyvsp[0].decl)); }
#line 1529 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 5:
#line 70 "src/eeyore/sysy.y"
                          { (yyval.comp_unit) = new NCompUnit(); root = (yyval.comp_unit); (yyval.comp_unit)->body.push_back((yyvsp[0].func_def)); }
#line 1535 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 9:
#line 80 "src/eeyore/sysy.y"
                                 { (yyval.decl_stmt) = (yyvsp[-1].decl_stmt); }
#line 1541 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 10:
#line 83 "src/eeyore/sysy.y"
                                       { (yyval.decl_stmt) = new NDeclareStmt((yyvsp[-1].token)); (yyval.decl_stmt)->decl_list.push_back((yyvsp[0].decl)); }
#line 1547 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 11:
#line 84 "src/eeyore/sysy.y"
                                           { (yyval.decl_stmt) = (yyvsp[-2].decl_stmt); (yyval.decl_stmt)->decl_list.push_back((yyvsp[0].decl)); }
#line 1553 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 14:
#line 91 "src/eeyore/sysy.y"
                                       { (yyval.decl) = new NVarDeclareWithInit(*(yyvsp[-2].ident), *(yyvsp[0].expr), true); }
#line 1559 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 15:
#line 94 "src/eeyore/sysy.y"
                                                   { (yyval.decl) = new NArrayDeclareWithInit(*(yyvsp[-2].array_ident), *(yyvsp[0].array_init_val), true); }
#line 1565 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 16:
#line 98 "src/eeyore/sysy.y"
                               { (yyval.decl_stmt) = (yyvsp[-1].decl_stmt); }
#line 1571 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 17:
#line 101 "src/eeyore/sysy.y"
                               { (yyval.decl_stmt) = new NDeclareStmt((yyvsp[-1].token)); (yyval.decl_stmt)->decl_list.push_back((yyvsp[0].decl)); }
#line 1577 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 18:
#line 102 "src/eeyore/sysy.y"
                                       { (yyval.decl_stmt) = (yyvsp[-2].decl_stmt); (yyval.decl_stmt)->decl_list.push_back((yyvsp[0].decl)); }
#line 1583 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 21:
#line 109 "src/eeyore/sysy.y"
                                       { (yyval.decl) = new NVarDeclareWithInit(*(yyvsp[-2].ident), *(yyvsp[0].expr), false); }
#line 1589 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 22:
#line 110 "src/eeyore/sysy.y"
                        { (yyval.decl) = new NVarDeclare(*(yyvsp[0].ident)); }
#line 1595 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 23:
#line 113 "src/eeyore/sysy.y"
                                                   { (yyval.decl) = new NArrayDeclareWithInit(*(yyvsp[-2].array_ident), *(yyvsp[0].array_init_val), false); }
#line 1601 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 24:
#line 114 "src/eeyore/sysy.y"
                               { (yyval.decl) = new NArrayDeclare(*(yyvsp[0].array_ident)); }
#line 1607 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 25:
#line 117 "src/eeyore/sysy.y"
                                                     { (yyval.array_ident) = (yyvsp[-3].array_ident); (yyval.array_ident)->shape.push_back((yyvsp[-1].expr)); }
#line 1613 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 26:
#line 118 "src/eeyore/sysy.y"
                                              { (yyval.array_ident) = new NArrayIdentifier(*(yyvsp[-3].ident)); (yyval.array_ident)->shape.push_back((yyvsp[-1].expr)); }
#line 1619 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 28:
#line 124 "src/eeyore/sysy.y"
                                                 { (yyval.array_init_val) = (yyvsp[-1].array_init_val); }
#line 1625 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 29:
#line 125 "src/eeyore/sysy.y"
                                  { (yyval.array_init_val) = new NArrayDeclareInitValue(false, nullptr); }
#line 1631 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 30:
#line 128 "src/eeyore/sysy.y"
                                                    { (yyval.array_init_val) = (yyvsp[-2].array_init_val); (yyval.array_init_val)->value_list.push_back((yyvsp[0].array_init_val)); }
#line 1637 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 31:
#line 129 "src/eeyore/sysy.y"
                                               { (yyval.array_init_val) = (yyvsp[-2].array_init_val); (yyval.array_init_val)->value_list.push_back(new NArrayDeclareInitValue(true, (yyvsp[0].expr))); }
#line 1643 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 32:
#line 130 "src/eeyore/sysy.y"
                               { 
                    (yyval.array_init_val) = new NArrayDeclareInitValue(false, nullptr);
                    (yyval.array_init_val)->value_list.push_back((yyvsp[0].array_init_val));
                }
#line 1652 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 33:
#line 134 "src/eeyore/sysy.y"
                          {
                    (yyval.array_init_val) = new NArrayDeclareInitValue(false, nullptr);
                    (yyval.array_init_val)->value_list.push_back(new NArrayDeclareInitValue(true, (yyvsp[0].expr)));
                }
#line 1661 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 35:
#line 144 "src/eeyore/sysy.y"
                                    { (yyval.expr) = new NBinaryExpr(*(yyvsp[-2].expr), (yyvsp[-1].token), *(yyvsp[0].expr)); }
#line 1667 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 37:
#line 148 "src/eeyore/sysy.y"
                                    { (yyval.expr) = new NBinaryExpr(*(yyvsp[-2].expr), (yyvsp[-1].token), *(yyvsp[0].expr)); }
#line 1673 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 39:
#line 152 "src/eeyore/sysy.y"
                                   { (yyval.expr) = new NBinaryExpr(*(yyvsp[-2].expr), (yyvsp[-1].token), *(yyvsp[0].expr)); }
#line 1679 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 40:
#line 153 "src/eeyore/sysy.y"
                                   { (yyval.expr) = new NBinaryExpr(*(yyvsp[-2].expr), (yyvsp[-1].token), *(yyvsp[0].expr)); }
#line 1685 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 43:
#line 158 "src/eeyore/sysy.y"
                                      { (yyval.expr) = new NBinaryExpr(*(yyvsp[-2].expr), (yyvsp[-1].token), *(yyvsp[0].expr)); }
#line 1691 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 44:
#line 161 "src/eeyore/sysy.y"
                                      { (yyval.expr) = new NBinaryExpr(*(yyvsp[-2].expr), (yyvsp[-1].token), *(yyvsp[0].expr)); }
#line 1697 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 46:
#line 165 "src/eeyore/sysy.y"
                                        { (yyval.expr) = new NBinaryExpr(*(yyvsp[-2].expr), (yyvsp[-1].token), *(yyvsp[0].expr)); }
#line 1703 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 48:
#line 169 "src/eeyore/sysy.y"
                                   { (yyval.expr) = new NUnaryExpr((yyvsp[-1].token), *(yyvsp[0].expr)); }
#line 1709 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 51:
#line 174 "src/eeyore/sysy.y"
                                                    { (yyval.expr) = new NFuncCall(*(yyvsp[-3].ident), *(yyvsp[-1].func_call_args));  }
#line 1715 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 52:
#line 175 "src/eeyore/sysy.y"
                                        { (yyval.expr) = new NFuncCall(*(yyvsp[-2].ident), *(new NFuncCallArgs())); }
#line 1721 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 53:
#line 178 "src/eeyore/sysy.y"
                                           { (yyval.func_call_args) = (yyvsp[-2].func_call_args); (yyval.func_call_args)->args.push_back((yyvsp[0].expr)); }
#line 1727 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 54:
#line 179 "src/eeyore/sysy.y"
                         { (yyval.func_call_args) = new NFuncCallArgs(); (yyval.func_call_args)->args.push_back((yyvsp[0].expr)); }
#line 1733 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 57:
#line 184 "src/eeyore/sysy.y"
                                       { (yyval.expr) = (yyvsp[-1].cond_expr); }
#line 1739 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 59:
#line 188 "src/eeyore/sysy.y"
                                             { (yyval.array_ident) = new NArrayIdentifier(*(yyvsp[-3].ident)); (yyval.array_ident)->shape.push_back((yyvsp[-1].expr)); }
#line 1745 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 60:
#line 189 "src/eeyore/sysy.y"
                                                  { (yyval.array_ident) = (yyvsp[-3].array_ident); (yyval.array_ident)->shape.push_back((yyvsp[-1].expr)); }
#line 1751 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 63:
#line 196 "src/eeyore/sysy.y"
                                                                { (yyval.func_def) = new NFuncDef((yyvsp[-5].token), *(yyvsp[-4].ident), *(yyvsp[-2].func_def_args), *(yyvsp[0].block)); }
#line 1757 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 64:
#line 197 "src/eeyore/sysy.y"
                                                    { (yyval.func_def) = new NFuncDef((yyvsp[-4].token), *(yyvsp[-3].ident), *(new NFuncDefArgs()), *(yyvsp[0].block)); }
#line 1763 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 65:
#line 198 "src/eeyore/sysy.y"
                                                               { (yyval.func_def) = new NFuncDef((yyvsp[-5].token), *(yyvsp[-4].ident), *(yyvsp[-2].func_def_args), *(yyvsp[0].block)); }
#line 1769 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 66:
#line 199 "src/eeyore/sysy.y"
                                                   { (yyval.func_def) = new NFuncDef((yyvsp[-4].token), *(yyvsp[-3].ident), *(new NFuncDefArgs()), *(yyvsp[0].block)); }
#line 1775 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 67:
#line 202 "src/eeyore/sysy.y"
                                               { (yyval.func_def_args) = (yyvsp[-2].func_def_args); (yyval.func_def_args)->args.push_back((yyvsp[0].func_def_arg)); }
#line 1781 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 68:
#line 203 "src/eeyore/sysy.y"
                             { (yyval.func_def_args) = new NFuncDefArgs(); (yyval.func_def_args)->args.push_back((yyvsp[0].func_def_arg)); }
#line 1787 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 71:
#line 210 "src/eeyore/sysy.y"
                              { (yyval.func_def_arg) = new NFuncDefArg((yyvsp[-1].token), *(yyvsp[0].ident)); }
#line 1793 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 72:
#line 213 "src/eeyore/sysy.y"
                                                  { 
                    auto ident = new NIdentifier((yyvsp[-2].func_def_arg)->ident.name);
                    auto array_ident = new NArrayIdentifier(*ident);
                    array_ident->shape.push_back(new NNumber(1));
                    (yyval.func_def_arg) = new NFuncDefArg((yyvsp[-2].func_def_arg)->type, *array_ident, true);
                }
#line 1804 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 73:
#line 219 "src/eeyore/sysy.y"
                                                        {  
                    (yyval.func_def_arg) = (yyvsp[-3].func_def_arg);
                    NArrayIdentifier& array_ident = (NArrayIdentifier&)(yyval.func_def_arg)->ident;
                    array_ident.shape.push_back((yyvsp[-1].expr));
                }
#line 1814 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 74:
#line 226 "src/eeyore/sysy.y"
                                  { (yyval.block) = new NBlock(); }
#line 1820 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 75:
#line 227 "src/eeyore/sysy.y"
                                             { (yyval.block) = (yyvsp[-1].block); }
#line 1826 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 76:
#line 230 "src/eeyore/sysy.y"
                            { (yyval.block) = new NBlock(); (yyval.block)->body.push_back((yyvsp[0].stmt)); }
#line 1832 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 77:
#line 231 "src/eeyore/sysy.y"
                                       { (yyval.block) = (yyvsp[-1].block); (yyval.block)->body.push_back((yyvsp[0].stmt)); }
#line 1838 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 87:
#line 245 "src/eeyore/sysy.y"
                           { (yyval.stmt) = new NEvalStmt(*(yyvsp[-1].expr)); }
#line 1844 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 88:
#line 246 "src/eeyore/sysy.y"
                       { (yyval.stmt) = new NVoidStmt(); }
#line 1850 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 89:
#line 249 "src/eeyore/sysy.y"
                                        { (yyval.stmt) = (yyvsp[-1].stmt); }
#line 1856 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 90:
#line 252 "src/eeyore/sysy.y"
                                     { (yyval.stmt) = new NAssignStmt(*(yyvsp[-2].ident), *(yyvsp[0].expr)); }
#line 1862 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 91:
#line 255 "src/eeyore/sysy.y"
                                               { (yyval.stmt) = new NIfStmt(*(yyvsp[-2].cond_expr), *(yyvsp[0].stmt)); }
#line 1868 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 92:
#line 256 "src/eeyore/sysy.y"
                                                         { (yyval.stmt) = new NIfElseStmt(*(yyvsp[-4].cond_expr), *(yyvsp[-2].stmt), *(yyvsp[0].stmt)); }
#line 1874 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 93:
#line 259 "src/eeyore/sysy.y"
                                  { (yyval.stmt) = new NReturnStmt((yyvsp[-1].expr)); }
#line 1880 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 94:
#line 260 "src/eeyore/sysy.y"
                              { (yyval.stmt) = new NReturnStmt(); }
#line 1886 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 95:
#line 263 "src/eeyore/sysy.y"
                                                  { (yyval.stmt) = new NWhileStmt(*(yyvsp[-2].cond_expr), *(yyvsp[0].stmt)); }
#line 1892 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 96:
#line 266 "src/eeyore/sysy.y"
                             { (yyval.stmt) = new NBreakStmt(); }
#line 1898 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 97:
#line 269 "src/eeyore/sysy.y"
                                { (yyval.stmt) = new NContinueStmt(); }
#line 1904 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 99:
#line 275 "src/eeyore/sysy.y"
                          { (yyval.expr) = new NNumber(*(yyvsp[0].string)); }
#line 1910 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;

  case 112:
#line 298 "src/eeyore/sysy.y"
                             { (yyval.ident) = new NIdentifier(*(yyvsp[0].string)); }
#line 1916 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"
    break;


#line 1920 "/home/mew/Git/SysY-Compiler/test/sysy.tab.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 301 "src/eeyore/sysy.y"


NCompUnit* parse()
{
    yyparse();
    return root;
}
