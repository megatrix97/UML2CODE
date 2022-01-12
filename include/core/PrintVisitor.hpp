#pragma once
#include "NodeVisitor.hpp"

namespace UML {
class PrintVisitor : public NodeVisitor {
  int currentIndentationLevel = 0;

public:
  void visit(Node *node);
  void visit(ClassDecl *classdecl);
  void visit(Variable *variable);
  void visit(Method *method);
};
} // namespace UML