#include "core/RequiredHeaders.hpp"
#include "core/UMLContext.hpp"
#include "file_io/FileWriter.hpp"
#include "utils/RelationshipDataProvider.hpp"
#include "plantuml_parser.hpp"
#include <iostream>
#include <memory>
#include <set>
#include <stdlib.h>
#include <string>
#include <unordered_map>

UML::RDP *rdp;
std::unordered_map<std::string, UML::ClassDecl *> parser_allClasses;
int main(int argc, char **argv) {
  extern FILE *yyin;
  if (argc != 2) {
    std::cerr << "No input file provided!\nExiting..." << std::endl;
    return EXIT_FAILURE;
  }
  yyin = fopen(argv[1], "r");
  std::cout << "[uml2code] parsing input" << std::endl;
  yyparse();
  std::cout << "[uml2code] completed parsing input " << std::endl;

  auto formatPref = std::make_unique<UML::FormatPref>();
  formatPref->setLanguage(UML::LANG::CPP)
      ->setIndentation(UML::INDENTATION::TAB)
      ->setDestinationDir("C:/Users/nithi/Desktop/test");

  std::cout << formatPref->getDestinationDir() << std::endl;

  // build UMLContext object
  std::vector<UML::ClassDecl *> listOfClasses;
  for (auto x : parser_allClasses) {
    listOfClasses.push_back(x.second);
  }
  auto umlContext =
      std::make_unique<UML::UMLContext>(listOfClasses, rdp, formatPref.get());

  auto p = std::make_unique<UML::PrintVisitor>();
  for (auto c : umlContext->getAllClasses()) p->visit(c);

  auto fw = std::make_unique<UML::FileWriter>(umlContext.get());
  fw->write();
  std::cout << "[uml2code] ran write command" << std::endl;
}
