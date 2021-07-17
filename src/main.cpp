#include "core/include/RequiredHeaders.hpp"
#include "file_io/include/FileWriter.hpp"
#include "flex_bison/tokens.tab.h"
#include <memory>

UML::Node *root;

int main(int argc, char **argv) {
  extern FILE *yyin;
  yyin = fopen(argv[1], "r");
  std::cout << "parsing input" << std::endl;
  yyparse();
  std::cout << "completed parsing input " << std::endl;
  UML::PrintVisitor *p = new UML::PrintVisitor();
  auto formatPref = std::make_shared<UML::FormatPref>();
  formatPref->setLanguage(UML::LANG::CPP).setIndentation(UML::INDENTATION::TAB);
  auto fw = std::make_unique<UML::FileWriter>(formatPref);
  p->visit(root);
  fw->write(root);
  std::cout << "ran write command" << std::endl;
}
