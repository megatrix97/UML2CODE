#include "plantuml_parser.hpp"
#include <iostream>
#include <stdio.h>

extern FILE *yyin;
std::unordered_map<std::string, UML::ClassDecl *> allClasses;
int main(int argc, char **argv) {
  yyin = fopen(argv[1], "r");
  yyparse();
  // printing relationship contents
  UML::RDP::printContents();
}