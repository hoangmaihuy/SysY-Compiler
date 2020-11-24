%{
#include "globals.hpp"
#include "tree.hpp"
#include "source.tab.hpp"

#define SAVE_TOKEN  yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t)    (yylval.token = t)
#define FIX_LINE    for (auto i : std::string(yytext_ptr)) { if (i == '\n') yylineno++; }
extern void yyerror(const char* s);
%}

%option noyywrap

digit           [0-9]
number          {digit}+
letter          [a-zA-Z]
letter_         [a-zA-Z_]
letter_digit    [a-zA-Z0-9_] 
integer         {number}+
identifier      {letter_}{letter_digit}* 
newline         \n
whitespace      [ \t\r]+



%%
"//"[^\n]*                  ;
"/*"                        {
                                int c;
                                while((c = yyinput()) != 0) {
                                    if(c == '\n')
                                        yylineno++;
                                    else if(c == '*') {
                                        if((c = yyinput()) == '/')
                                            break;
                                        else
                                            unput(c);
                                        }
                                }
                            }
{whitespace}                ;
{newline}                   yylineno++;
"if"                        return TOKEN(IF);
"else"                      return TOKEN(ELSE);
"while"                     return TOKEN(WHILE);
"break"                     return TOKEN(BREAK);
"continue"                  return TOKEN(CONTINUE);
"return"                    return TOKEN(RETURN);
"const"                     return TOKEN(CONST);
"int"                       return TOKEN(INT);
"void"                      return TOKEN(VOID);
"starttime"[ \t\n]*"("      FIX_LINE; yylval.string = new std::string("_sysy_starttime"); *yy_cp = yy_hold_char; yy_hold_char='(';yy_cp--; yyleng--; yy_c_buf_p--; *yy_c_buf_p='_';yy_c_buf_p--; *yy_c_buf_p='_';yy_c_buf_p--; *yy_c_buf_p='E';yy_c_buf_p--; *yy_c_buf_p='N';yy_c_buf_p--; *yy_c_buf_p='I';yy_c_buf_p--; *yy_c_buf_p='L';yy_c_buf_p--; *yy_c_buf_p='_';yy_c_buf_p--; *yy_c_buf_p='_';yy_c_buf_p--; return IDENTIFIER;
"stoptime"[ \t\n]*"("       FIX_LINE; yylval.string = new std::string("_sysy_stoptime"); *yy_cp = yy_hold_char; yy_hold_char='(';yy_cp--; yyleng--; yy_c_buf_p--; *yy_c_buf_p='_';yy_c_buf_p--; *yy_c_buf_p='_';yy_c_buf_p--; *yy_c_buf_p='E';yy_c_buf_p--; *yy_c_buf_p='N';yy_c_buf_p--; *yy_c_buf_p='I';yy_c_buf_p--; *yy_c_buf_p='L';yy_c_buf_p--; *yy_c_buf_p='_';yy_c_buf_p--; *yy_c_buf_p='_';yy_c_buf_p--; return IDENTIFIER;
"__LINE__"                  yylval.string = new std::string(std::to_string(yyget_lineno())); return INTEGER;
{identifier}                SAVE_TOKEN; return IDENTIFIER;
{integer}                   SAVE_TOKEN; return INTEGER;
"0x"[0-9a-fA-F]+            SAVE_TOKEN; return INTEGER;

"="                         return TOKEN(ASSIGN);
"=="                        return TOKEN(EQ);
"!="                        return TOKEN(NE);
"<"                         return TOKEN(LT);
"<="                        return TOKEN(LE);
">"                         return TOKEN(GT);
">="                        return TOKEN(GE);
"&&"                        return TOKEN(AND);
"||"                        return TOKEN(OR);

"("                         return TOKEN(L_PAREN);
")"                         return TOKEN(R_PAREN);
"["                         return TOKEN(L_SQUARE);
"]"                         return TOKEN(R_SQUARE);
"{"                         return TOKEN(L_BRACE);
"}"                         return TOKEN(R_BRACE);

","                         return TOKEN(COMMA);
";"                         return TOKEN(SEMI);

"+"                         return TOKEN(PLUS);
"-"                         return TOKEN(MINUS);
"*"                         return TOKEN(MUL);
"/"                         return TOKEN(DIV);
"%"                         return TOKEN(MOD);
"!"                         return TOKEN(NOT);

.                           yyerror(strcat("Unknown token: ", yytext));
%%