#include "../../include/core/PrintVisitor.hpp"
#include "../../include/core/ClassDecl.hpp"
#include "../../include/core/Method.hpp"
#include "../../include/core/Variable.hpp"

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
  std::cout << "[Method]" << method->getId() << std::endl;
  std::cout << "-------[ReturnType]" << method->getType() << std::endl;
  std::cout << "-------[InputArgs ]" << std::endl;
  auto inputArgs = method->getInputArgList();

  currentIndentationLevel++;
  for (auto arg : inputArgs) {
    arg->accept(this);
  }
  currentIndentationLevel--;
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