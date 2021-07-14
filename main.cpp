#include "RequiredHeaders.hpp"
#include "tokens.tab.h"
#include <stdio.h>

UML::Node *root;

int main(int argc, char **argv) {
  extern FILE *yyin;
  yyin = fopen(argv[1], "r");
  yyparse();

  UML::PrintVisitor *p = new UML::PrintVisitor();
  UML::FormatPref *formatPref = new UML::FormatPref();
  formatPref->setLanguage(UML::LANG::CPP)
      .setIndentation(UML::INDENTATION::TAB)
      .setIndentation(UML::INDENTATION::DEFAULT);
  p->visit(root);
}