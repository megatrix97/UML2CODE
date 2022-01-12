#include "core/PrintVisitor.hpp"
#include "parser.hpp"
#include <gtest/gtest.h>
#include <memory>

UML::Node *root;
std::unordered_set<std::string> TypeTable;

UML::Node *parseString(char *inputString) {
  YY_BUFFER_STATE buffer = yy_scan_string(inputString);
  yyparse();
  yy_delete_buffer(buffer);
  return root;
}

TEST(CPPEmitter, test1) {
  char inputString[] = "class NewClass{int x; int y; void newFunc(int x);};\0";
  auto rootNode = parseString(inputString);
  auto pv = std::make_unique<UML::PrintVisitor>();
  pv->visit(rootNode);
  EXPECT_EQ(1, 1);
}
