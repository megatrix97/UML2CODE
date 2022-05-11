%option noyywrap yylineno

%{
    #include <iostream>
    #include "plantuml_parser.hpp"
%}

START "@startuml"
END "@enduml"
CLASS "class"
ID [_a-zA-Z][_a-zA-Z0-9]*
NEWLINE [\r\n]+

%%

{START} { return START; }
{END} { return END; }
{CLASS} { return CLASS; }

    /* parentheses: start */
"{" { return LCURLY; }
"}" { return RCURLY; }
"(" { return LPAREN; }
")" { return RPAREN; }
"[" { return LSQUARE; }
"]" { return RSQUARE; }
    /* parentheses: end  */

{ID} { yylval.id = (char *) malloc(sizeof(char) * (strlen(yytext)+1)); 
                          strcpy (yylval.id, yytext); 
                          yylval.id[strlen(yytext)] = '\0'; return ID; }

{NEWLINE} { /* ignore newline*/ }
":" { return COLON; } 
"," { return COMMA; }

    /* relation arrows: start */
"o--"   { return AGGREGATION; }
"<\|--" { return INHERITANCE; }
"\*--"  { return COMPOSITION; }
"<\.\." { return DEPENDENCY; }
"<--"   { return ASSOCIATION; }
    /* relation arrows: end  */

    /* label: start */
">" { return RIGHT_ARROW; }
"<" { return LEFT_ARROW; }
    /* label: end */

    /* visibility: start */
"+" { return PUBLIC; }
"-" { return PRIVATE; }
"#" { return PROTECTED; }
    /* visibility: end */

%%