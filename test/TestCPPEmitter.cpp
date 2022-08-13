#include "file_io/cpp_emitter/CPPEmitter.hpp"
#include "plantuml_parser.hpp"
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <string.h>

UML::RelationshipDataProvider *rdp = new UML::RelationshipDataProvider();
std::unordered_map<std::string, UML::ClassDecl *> parser_allClasses;

class CPPEmitterTest : public ::testing::Test {
 protected:
  UML::FormatPref *formatPref;
  CPPEmitterTest() = default;

  void SetUp() {
    formatPref = new UML::FormatPref();
    formatPref->setLanguage(UML::LANG::CPP);
  }

  void TearDown() {
    delete rdp;
    delete formatPref;
    parser_allClasses.clear();
  }

  void parseString(std::string inputString) {
    int n = inputString.length();
    char arr[n + 1];
    strcpy_s(arr, n + 1, inputString.c_str());
    YY_BUFFER_STATE buffer = yy_scan_string(arr);
    yyparse();
    yy_delete_buffer(buffer);
  }
};

TEST_F(CPPEmitterTest, checkHPPAndCPP) {
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

  std::string outputString = R"(#pragma once
class second {
std::string m_name;
int m_value;
};)";

  parseString(inputString);
  EXPECT_EQ(parser_allClasses.size(), 2);

  // test emit hpp contents
  std::vector<UML::ClassDecl *> allClasses;
  for (auto x : parser_allClasses) {
    allClasses.push_back(x.second);
  }
  auto umlContext =
      std::make_unique<UML::UMLContext>(allClasses, rdp, formatPref);
  auto cppEmitter = std::make_unique<UML::CPPEmitter>(umlContext.get());
  EXPECT_THAT(cppEmitter->emit<false>(allClasses[0]),
              ::testing::HasSubstr(outputString));
}
