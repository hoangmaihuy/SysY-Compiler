%{
#include "globals.hpp"
#include "tree.hpp"
#include "source.tab.hpp"

#define SAVE_TOKEN  yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t)    (yylval.token = t)
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
whitespace      [ \t]+



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