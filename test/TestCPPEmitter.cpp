#include "file_io/cpp_emitter/CPPEmitter.hpp"
#include "plantuml_parser.hpp"
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <string.h>

UML::RDP *rdp;
std::unordered_map<std::string, UML::ClassDecl *> parser_allClasses;

void parseString(std::string inputString) {
  int n = inputString.length();
  char arr[n + 1];
  strcpy_s(arr, n + 1, inputString.c_str());
  YY_BUFFER_STATE buffer = yy_scan_string(arr);
  yyparse();
  yy_delete_buffer(buffer);
}

TEST(CPPEmitter, checkHPPAndCPP) {
  std::string inputString = R"(@startuml
  class first {
    string name
    int value
  }

  class second {
    + string name
    + int value
  }

  @enduml)";

  parseString(inputString);
  EXPECT_EQ(parser_allClasses.size(), 2);
  std::cout << "Test parsing complete" << std::endl;
}
