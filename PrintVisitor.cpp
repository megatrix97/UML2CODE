#include "PrintVisitor.hpp"
#include "ClassDecl.hpp"
#include "Method.hpp"
#include "Variable.hpp"

namespace UML {
void PrintVisitor::visit(Node *node) { node->accept(this); }
void PrintVisitor::visit(ClassDecl *classdecl) {
  std::cout << classdecl->getId() << "class details:" << std::endl;
  std::cout << "------------------------------------" << std::endl;
  std::cout << "List of attributes" << std::endl;
  auto attributes = classdecl->getAttributeList();
  for (auto attribute : *attributes) {
    visit(attribute);
  }
}
void PrintVisitor::visit(Method *method) {
  std::cout << "[Method]" << method->getId() << std::endl;
  std::cout << "-------[ReturnType]" << method->getType() << std::endl;
  std::cout << "-------[InputArgs ]" << std::endl;
  auto inputArgs = method->getInputArgList();
  for (auto arg : *inputArgs) {
    currentIndentationLevel = 1;
    arg->accept(this);
  }
  currentIndentationLevel = 0;
}

void PrintVisitor::visit(Variable *variable) {
  std::string indent;
  if (currentIndentationLevel != 0)
    indent = std::string(currentIndentationLevel * 8, ' ');
  else
    indent = "";
  std::cout << indent << "[Variable]" << variable->getId() << std::endl;
  std::cout << indent << "---------[Type]" << variable->getType() << std::endl;
}
} // namespace UML