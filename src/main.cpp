#include "core/include/RequiredHeaders.hpp"
#include "core/include/UMLData.hpp"
#include "file_io/include/FileWriter.hpp"
#include "flex_bison/tokens.tab.h"
#include <memory>
#include <set>
#include <unordered_map>

UML::Node *root;
std::unordered_map<std::string, std::string> TypeTable;

int main(int argc, char **argv) {
  extern FILE *yyin;
  yyin = fopen(argv[1], "r");
  std::cout << "parsing input" << std::endl;
  yyparse();
  std::cout << "completed parsing input " << std::endl;
  std::cout << "-- TypeTable Contents --" << std::endl;
  for (auto entry : TypeTable)
    std::cout << entry.first << " " << entry.second << std::endl;

  auto p = std::make_unique<UML::PrintVisitor>();

  auto umlData = UML::UMLData(root, TypeTable);

  auto formatPref = std::make_shared<UML::FormatPref>();
  formatPref->setLanguage(UML::LANG::CPP).setIndentation(UML::INDENTATION::TAB);

  auto fw = std::make_unique<UML::FileWriter>(formatPref);

  p->visit(root);
  fw->write(umlData);
  std::cout << "ran write command" << std::endl;
}
