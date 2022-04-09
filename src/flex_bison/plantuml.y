%code requires {
    #include <stdio.h>
    #include <iostream>
    #include <unordered_map>
    #include <vector>
    #include "core/Attribute.hpp"
    #include "core/ClassDecl.hpp"
    #include "core/RequiredHeaders.hpp"
    #include "utils/RelationshipDataProvider.hpp"

    extern FILE *yyin;
    extern int yylineno;
    extern int yylex();
    void yyerror(const char* s);
    extern std::unordered_map<std::string, UML::ClassDecl*> allClasses;
    UML::ClassDecl* getClass(std::string className);
}

%union{
    char* id;
    UML::ACCESS access;
    UML::RELATION relation;
    UML::Attribute* attr;
    std::vector<UML::Attribute*>* attr_list;
    std::vector<UML::Variable*>* var_list;
}

%start body

%token START END
%token CLASS
%token <id> ID
%token LCURLY RCURLY LPAREN RPAREN LSQUARE RSQUARE
%token <relation> AGGREGATION INHERITANCE COMPOSITION DEPENDENCY ASSOCIATION
%token <access> PUBLIC PROTECTED PRIVATE
%token RIGHT_ARROW LEFT_ARROW
%token COLON COMMA

%type <access> visibility
%type <relation> relationship
%type <attr> attribute field method
%type <attr_list> attribute_list
%type <var_list> arg_list

%%
body
    : START info END
    ;

info
    : class_relationship
    | class_decl
    | class_def
    | attribute_info
    | info class_relationship
    | info class_decl
    | info class_def
    ;

class_relationship
    : ID relationship ID {
        std::cout << "found a relationship : " << $1 << " relation: " << $2 << " " << $3 << std::endl;
        std::string parentClassName = std::string($1);
        std::string childClassName = std::string($3);
        UML::ClassDecl* parent = getClass(std::string($1));
        UML::ClassDecl* child = getClass(std::string($3));
        if(parent == null) {
            parent = new UML::ClassDecl(std::string($1));
            allClasses.insert(parentClassName, parentClass);
        }
        if(child == null) {
            child = new UML::ClassDecl(std::string($3));
            allClasses.insert(childClassName, childClass);
        }
        RDP::setRelationshipData(parent, child, $2);
    }
    ;

relationship
    : AGGREGATION { $$ = UML::RELATION::AGGREGATION; }
    | INHERITANCE { $$ = UML::RELATION::INHERITANCE; }
    | COMPOSITION { $$ = UML::RELATION::COMPOSITION; }
    | DEPENDENCY  { $$ = UML::RELATION::DEPENDENCY; }
    | ASSOCIATION { $$ = UML::RELATION::ASSOCIATION; }
    ;

class_def
    : CLASS ID LCURLY attribute_list RCURLY {
        std::cout << "found class \"" << $2 << "\" definition" << std::endl;
        UML::ClassDecl* cdecl = new UML::ClassDecl($2, *$4);
        cdecl->accept(new UML::PrintVisitor());
    }
    ;

class_decl
    : CLASS ID {
        std::cout << "found class \"" << $2 << "\" declaration" << std::endl;
    }
    ;

attribute_info
    : ID COLON field {
        std::cout << "found field for class: " << $1 << std::endl;
    }
    | ID COLON method {
        std::cout << "found method for class: " << $1 << std::endl;
    }

attribute_list
    : attribute {
        $$ = new std::vector<UML::Attribute*>();
        $$->push_back($1);
    }
    | attribute_list attribute {
        $1->push_back($2);
        $$ = $1;
    }
    ;

attribute
    : field 
    | method
    | visibility field {
        std::cout << "visibility of field: " << $2->getId() << " is : " << (UML::AccessType::getInstance($1))->toString() << std::endl;
        $2->setAccessType(UML::AccessType::getInstance($1));
        $$ = $2;
    }
    | visibility method {
        std::cout << "visibility of method : " << $2->getId() << " is: " << (UML::AccessType::getInstance($1))->toString() << std::endl;
        $2->setAccessType(UML::AccessType::getInstance($1));
        $$ = $2;
    }
    ;

field
    : ID ID {
        $$ = new UML::Variable($1, $2);
    }
    | ID LSQUARE RSQUARE ID {
        std::string type = std::string($1) + "[]";
        $$ = new UML::Variable(type, $4);
    }
    ;

method
    : ID ID LPAREN RPAREN {
        $$ = new UML::Method($1, $2, {});
    }
    | ID ID LPAREN arg_list RPAREN {
        $$ = new UML::Method($1, $2, *$4);
    }
    ;

arg_list
    : field {
        $$ = new std::vector<UML::Variable*>();
        $$->push_back(dynamic_cast<UML::Variable*>($1));
    }
    | arg_list COMMA field {
        $1->push_back(dynamic_cast<UML::Variable*>($3));
        $$ = $1;
    }
    ;

visibility
    : PUBLIC    { $$ = UML::ACCESS::PUBLIC; }
    | PROTECTED { $$ = UML::ACCESS::PROTECTED; }
    | PRIVATE   { $$ = UML::ACCESS::PRIVATE; }
    ;

%%

UML::ClassDecl* getClass(std::string className){
    if(allClasses.find(className) != allClasses.end()) return allClasses[className];
    return nullptr;
}

void yyerror(const char* s){
    fprintf(stderr, "error: %s\n at line: %d\n", s, yylineno);
}