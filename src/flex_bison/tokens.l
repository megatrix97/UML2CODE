%option noyywrap yylineno
%{
    #include <iostream>
    #include "RequiredHeaders.hpp"
    #include "parser.hpp"
%}

IDENTIFIER [_a-zA-Z][a-zA-Z_0-9]*
CLASS "class"
TYPE "int"|"string"|"void"

%%

{CLASS} { return CLASS; }
{TYPE} { yylval.id = (char *) malloc(sizeof(char) * (strlen(yytext)+1)); 
                          strcpy (yylval.id, yytext); 
                          yylval.id[strlen(yytext)] = '\0'; return TYPE; }
"{" { return OPEN_CURLY; }
"}" { return CLOSE_CURLY; }
"(" { return OPEN_PAREN; }
")" { return CLOSE_PAREN; }
";" { return SEMICOLON; }
"," { return COMMA; }
{IDENTIFIER} { yylval.id = (char *) malloc(sizeof(char) * (strlen(yytext)+1)); 
                          strcpy (yylval.id, yytext); 
                          yylval.id[strlen(yytext)] = '\0'; return ID; }
[ \n\t] {/* ignore whitespaces */}

%%
