#include "core/UMLData.hpp"
#include "file_io/cpp_emitter/CPPEmitter.hpp"
#include "parser.hpp"
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <string.h>

UML::Node *root;
std::unordered_set<std::string> TypeTable;

UML::Node *parseString(std::string inputString) {
  int n = inputString.length();
  char arr[n + 1];
  strcpy_s(arr, n + 1, inputString.c_str());
  YY_BUFFER_STATE buffer = yy_scan_string(arr);
  yyparse();
  yy_delete_buffer(buffer);
  return root;
}

// TEST(CPPEmitter, checkHPPAndCPP) {
//   std::string inputString = R"(class NewClass
//                             {
//                               int x;
//                               int y;
//                               void newFunc(int x);
//                             };
//                             )";
//   std::string expectedStringHpp = R"(#pragma once
// class NewClass {
// int m_x;
// int m_y;
// void newFunc(int x);
// public:
// int getX();
// void setX(int x);
// int getY();
// void setY(int y);
// };)";
//   std::string expectedStringCpp = R"(void NewClass::newFunc(int x) {
// }
// int NewClass::getX() {
// }
// void NewClass::setX(int x) {
// }
// int NewClass::getY() {
// }
// void NewClass::setY(int y) {
// })";
//   auto rootNode = parseString(inputString);
//   auto umlData = std::make_unique<UML::UMLData>(rootNode, TypeTable);
//   UML::CPPEmitter cppemitter(umlData.get());
//   std::string outputString = cppemitter.emit<false>();

//   EXPECT_THAT(outputString, testing::HasSubstr(expectedStringHpp));

//   outputString = cppemitter.emit<true>();
//   EXPECT_THAT(outputString, testing::HasSubstr(expectedStringCpp));
// }
