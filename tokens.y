%{
    #include <iostream>
    #include <vector>
    #include "RequiredHeaders.hpp"
    extern FILE *yyin;
    extern int yylineno;
    extern int yylex();
    void yyerror(const char* s);
    extern UML::Node* root;
%}

%start body

%union {
    char* id;
    UML::Node* node;
    UML::ClassDecl* class_decl;
    UML::Attribute* attribute;
    std::vector<UML::Attribute*>* attribute_list;
    std::vector<UML::Variable*>* func_input_args_list;
}

%token CLASS
%token <id> ID TYPE
%token OPEN_CURLY CLOSE_CURLY OPEN_PAREN CLOSE_PAREN
%token SEMICOLON COMMA

%type <node> body
%type <class_decl> classdecl 
%type <attribute> attribute vardecl funcdecl
%type <attribute_list> attribute_list
%type <func_input_args_list> varlist

%define parse.error verbose

%%

body: classdecl {
    root = $1;
    $$ = $1;
}
;

classdecl: CLASS ID OPEN_CURLY attribute_list CLOSE_CURLY SEMICOLON {
    $$ = new UML::ClassDecl($2, $4);
}
;

attribute_list: attribute_list attribute {
    $1->push_back($2);
    $$ = $1;
}
| attribute {
    $$ = new std::vector<UML::Attribute*>();
    $$->push_back($1); 
}
;

attribute: funcdecl
| vardecl
;

vardecl: TYPE ID SEMICOLON {
    $$ = new UML::Variable($1, $2);
}
;

funcdecl: TYPE ID OPEN_PAREN varlist CLOSE_PAREN SEMICOLON{
    $$ = new UML::Method($1, $2, $4);
}
;

varlist: TYPE ID {
    $$ = new std::vector<UML::Variable*>();
    $$->push_back(new UML::Variable($1, $2));
}
| varlist COMMA TYPE ID {
    $1->push_back(new UML::Variable($3, $4));
    $$ = $1;
}
;

%%

void yyerror(const char* s){
    fprintf(stderr, "error: %s\n at line: %d\n", s, yylineno);
}
