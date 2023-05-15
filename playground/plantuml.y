%code requires {
    #include <stdio.h>
    #include <iostream>
    #include <unordered_map>
    #include <vector>
    #include "core/Attribute.hpp"
    #include "core/ClassDecl.hpp"
    #include "core/RequiredHeaders.hpp"
    #include "core/UMLContext.hpp"
    #include "utils/RelationshipDataProvider.hpp"

    extern FILE *yyin;
    extern int yylineno;
    extern int yylex();
    extern UML::UMLContext* umlContext;
    void yyerror(const char* s);
    UML::RelationshipDataProvider* rdp;
    std::unordered_map<std::string, UML::ClassDecl*> allClasses;
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
    : START info END {
        std::vector<UML::ClassDecl*> listOfClasses;
        for(auto x: allClasses){
            listOfClasses.push_back(x.second);
        }
        umlContext = new UML::UMLContext(listOfClasses, rdp, nullptr);
    }
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
        UML::ClassDecl* parent = getClass(parentClassName);
        UML::ClassDecl* child = getClass(childClassName);
        if(parent == nullptr) {
            parent = new UML::ClassDecl(parentClassName);
            allClasses.insert(std::make_pair(parentClassName, parent));
        }
        if(child == nullptr) {
            child = new UML::ClassDecl(childClassName);
            allClasses.insert(std::make_pair(childClassName, child));
        }
        if(rdp == nullptr) rdp = new UML::RelationshipDataProvider();
        rpd->setRelationshipData(parent, child, $2);    
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
        UML::ClassDecl* cdecl = new UML::ClassDecl($2, *$4);
        allClasses.insert(std::make_pair(cdecl->getId(), cdecl));
    }
    ;

class_decl
    : CLASS ID {
        UML::ClassDecl* cdecl = new UML::ClassDecl($2);
        allClasses.insert(std::make_pair(cdecl->getId(), cdecl));
    }
    ;

attribute_info
    : ID COLON field {
        UML::ClassDecl* cdecl = getClass(std::string($1));
        if(cdecl == nullptr) {
            cdecl = new UML::ClassDecl($1);
            allClasses.insert(std::make_pair(cdecl->getId(), cdecl));
        }
        cdecl->addAttribute($3);
    }
    | ID COLON method {
        UML::ClassDecl* cdecl = getClass(std::string($1));
        if(cdecl == nullptr) {
            cdecl = new UML::ClassDecl($1);
            allClasses.insert(std::make_pair(cdecl->getId(), cdecl));
        }
        cdecl->addAttribute($3);
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
        $2->setAccessType(UML::AccessType::getInstance($1));
        $$ = $2;
    }
    | visibility method {
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