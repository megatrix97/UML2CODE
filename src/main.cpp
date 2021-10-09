#include "core/include/RequiredHeaders.hpp"
#include "core/include/TypeHeaderParser.hpp"
#include "core/include/UMLData.hpp"
#include "file_io/include/FileWriter.hpp"
#include "flex_bison/tokens.tab.h"
#include <memory>
#include <set>
#include <unordered_map>

UML::Node *root;
std::unordered_set<std::string> TypeTable;

int main(int argc, char **argv) {
  extern FILE *yyin;
  yyin = fopen(argv[1], "r");
  std::cout << "parsing input" << std::endl;
  yyparse();
  std::cout << "completed parsing input " << std::endl;
  std::cout << "-- TypeTable Contents --" << std::endl;
  for (auto entry : TypeTable)
    std::cout << entry << std::endl;

  TypeHeaderParser thParser("../CPPTypeheaders.txt");
  thParser.parse();
  auto info = thParser.getParsedInfo();
  for (auto el : info) {
    std::cout << "Type : " << el.first << " details : "
              << "[ namespace: " << el.second.m_namespace
              << ", header: " << el.second.m_headerfile << " ]" << std::endl;
  }

  auto p = std::make_unique<UML::PrintVisitor>();

  auto umlData = std::make_shared<UML::UMLData>(root, TypeTable, info);

  auto formatPref = std::make_shared<UML::FormatPref>();
  formatPref->setLanguage(UML::LANG::CPP).setIndentation(UML::INDENTATION::TAB);

  auto fw = std::make_unique<UML::FileWriter>(formatPref);

  p->visit(root);
  fw->write(umlData);
  std::cout << "ran write command" << std::endl;
}
