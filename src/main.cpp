#include "core/RequiredHeaders.hpp"
#include "core/UMLData.hpp"
#include "file_io/FileWriter.hpp"
#include "file_io/cpp_emitter/TypeHeaderParser.hpp"
#include "parser.hpp"
#include <iostream>
#include <memory>
#include <set>
#include <stdlib.h>
#include <string>
#include <unordered_map>

UML::Node *root;
std::unordered_set<std::string> TypeTable;

int main(int argc, char **argv) {
  extern FILE *yyin;
  if (argc != 2) {
    std::cerr << "No input file provided!\nExiting..." << std::endl;
    return EXIT_FAILURE;
  }
  yyin = fopen(argv[1], "r");
  std::cout << "parsing input" << std::endl;
  yyparse();
  std::cout << "completed parsing input " << std::endl;
  std::cout << "-- TypeTable Contents --" << std::endl;
  for (auto entry : TypeTable)
    std::cout << entry << std::endl;

  auto p = std::make_unique<UML::PrintVisitor>();

  auto umlData = std::make_unique<UML::UMLData>(root, TypeTable);

  auto formatPref = std::make_unique<UML::FormatPref>();
  formatPref->setLanguage(UML::LANG::CPP).setIndentation(UML::INDENTATION::TAB);

  auto fw = std::make_unique<UML::FileWriter>(formatPref.get());

  p->visit(root);
  fw->write(umlData.get());
  std::cout << "ran write command" << std::endl;
}
