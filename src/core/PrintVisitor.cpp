#include "core/PrintVisitor.hpp"
#include "core/ClassDecl.hpp"
#include "core/Method.hpp"
#include "core/Variable.hpp"

namespace UML {
void PrintVisitor::visit(Node *node) { node->accept(this); }
void PrintVisitor::visit(ClassDecl *classdecl) {
  std::cout << classdecl->getId() << " details:" << std::endl;
  std::cout << "------------------------------------" << std::endl;
  std::cout << "List of attributes" << std::endl;
  auto attributes = classdecl->getAttributeList();
  for (auto attribute : attributes) {
    attribute->accept(this);
  }
}
void PrintVisitor::visit(Method *method) {
  std::cout << "method: { name: \"" << method->getId() << "\", " << std::endl;
  std::cout << "returntype: \"" << method->getType() << "\", " << std::endl;
  std::cout << "inputargs: \"[" << std::endl;
  auto inputArgs = method->getInputArgList();
  for (int i = 0; i < inputArgs.size(); i++) {
    inputArgs[i]->accept(this);
    if (i < inputArgs.size() - 1)
      std::cout << ", ";
  }
  std::cout << "]}" << std::endl;
}

void PrintVisitor::visit(Variable *variable) {
  std::cout << "variable: { name: \"" << variable->getId() << "\"" << std::endl;
  std::cout << "Type: \"" << variable->getType() << "\"}" << std::endl;
}
} // namespace UML