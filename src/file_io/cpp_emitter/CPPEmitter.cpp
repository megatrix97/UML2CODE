#include "include/CPPEmitter.hpp"

namespace UML {

std::string declareVariable(Variable *var) {
  // Ex: int m_var;
  return var->getType() + " m_" + var->getId() + ";";
}

std::string declareFunction(Method *method) {
  auto argList = method->getInputArgList();
  std::string argsDecl;
  for (auto arg = argList.begin(); arg != argList.end(); arg++) {
    argsDecl += (*arg)->getType();
    if (arg + 1 != argList.end())
      argsDecl += ", ";
  }
  return method->getType() + " " + method->getId() + "( " + argsDecl + " );";
}

void CPPEmitter::visit(Node *node) { node->accept(this); }

void CPPEmitter::visit(ClassDecl *classdecl) {
  /// writing HPP file

  // Adding header guards
  m_outFile << CPPEmitterTools::startHeaderGuard(classdecl->getId())
            << std::endl;

  // class declaration
  m_outFile << "class " << classdecl->getId() << " {" << std::endl;
  auto attributeList = classdecl->getAttributeList();
  std::vector<Method *> getSetList;
  // declare variables first
  for (auto attr : attributeList) {
    if (auto var = dynamic_cast<Variable *>(attr)) {
      m_outFile << declareVariable(var) << std::endl;
      // add getter and setter functions for variable with private and protected
      // access
      getSetList.push_back(
          new Method(var->getType(), "get" + var->getId(), {}));
      getSetList.push_back(
          new Method("void", "set" + var->getId(),
                     {new Variable(var->getType(), var->getId())}));
    }
  }

  // declare methods
  for (auto attr : attributeList) {
    if (auto method = dynamic_cast<Method *>(attr))
      m_outFile << declareFunction(method) << std::endl;
  }

  // declare get set methods
  for (auto method : getSetList) {
    m_outFile << declareFunction(method) << std::endl;
  }

  m_outFile << "}; " << std::endl;

  // end header guards
  m_outFile << CPPEmitterTools::endHeaderGuard(classdecl->getId()) << std::endl;
}

void CPPEmitter::visit(Method *method) { /* do nothing */
}

void CPPEmitter::visit(Variable *variable) { /* do nothing */
}

} // namespace UML