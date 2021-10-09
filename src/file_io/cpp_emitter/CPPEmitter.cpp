#include "include/CPPEmitter.hpp"
#include "../include/EmitterTools.hpp"
#include <utility>

namespace UML {

inline std::string CPPEmitter::resolveScope(std::string type) {
  if (m_umlData->getTypeHeaderInfo().find(type) ==
      m_umlData->getTypeHeaderInfo().end())
    return type;

  auto nmspc = m_umlData->getTypeHeaderInfo()[type].m_namespace;
  if (!nmspc.empty()) {
    return nmspc + "::" + type;
  } else
    return type;
}

void CPPEmitter::emit() { visit(m_umlData->getNode()); }

void CPPEmitter::visit(Node *node) { node->accept(this); }

void CPPEmitter::visit(ClassDecl *classdecl) {
  /// preparing to write to HPP file
  m_outFile.open(classdecl->getId() + ".hpp");
  m_forDef = false;

  /// writing to HPP file

  // Adding header guards
  m_outFile << CPPEmitterTools::startHeaderGuard(classdecl->getId())
            << std::endl;

  // include required libraries
  auto allTypes = classdecl->getTypesInvolved();
  for (auto type : allTypes) {
    if (m_umlData->getTypeHeaderInfo().find(type) !=
        m_umlData->getTypeHeaderInfo().end()) {
      m_outFile << "#include<"
                << m_umlData->getTypeHeaderInfo()[type].m_headerfile << ">"
                << std::endl;
    }
  }

  // class declaration
  m_outFile << "class " << classdecl->getId() << " {" << std::endl;

  auto attributeList = classdecl->getAttributeList();

  // declare variables first
  for (auto attr : attributeList) {
    if (Variable::isa(attr)) {
      visit(attr);
      // add getter and setter functions for variable with private and protected
      // access
      auto getMethod =
          new Method(attr->getType(),
                     "get" + EmitterTools::firstLetterToUpper(attr->getId()),
                     {}, ACCESS::PUBLIC);
      getMethod->setClass(classdecl);
      auto setMethod = new Method(
          "void", "set" + EmitterTools::firstLetterToUpper(attr->getId()),
          {new Variable(attr->getType(), attr->getId())}, ACCESS::PUBLIC);
      setMethod->setClass(classdecl);
      attributeList.push_back(getMethod);
      attributeList.push_back(setMethod);
    }
  }

  auto isMethodOfAccessType = [](Attribute *aAttribute,
                                 ACCESS aAccess) -> bool {
    return Method::isa(aAttribute) && aAttribute->getAccessType() == aAccess;
  };

  // declare private methods
  for (auto attr : attributeList) {
    if (isMethodOfAccessType(attr, ACCESS::PRIVATE))
      visit(attr);
  }

  m_outFile << "public: " << std::endl;

  // declare public methods
  for (auto attr : attributeList) {
    if (isMethodOfAccessType(attr, ACCESS::PUBLIC))
      visit(attr);
  }

  m_outFile << "}; " << std::endl;

  // end header guards
  m_outFile << CPPEmitterTools::endHeaderGuard(classdecl->getId()) << std::endl;

  // close file
  m_outFile.close();

  // add header file for the new class type
  HeaderInfo aHeaderInfo = {"", classdecl->getId() + ".hpp"};
  m_umlData->getTypeHeaderInfo().insert(
      std::make_pair(classdecl->getId(), aHeaderInfo));

  /// preparing to write to CPP file
  m_outFile.open(classdecl->getId() + ".cpp");
  m_forDef = true;

  // include required libraries
  m_outFile << "#include \"" << classdecl->getId() + ".hpp"
            << "\"" << std::endl;
  // writing to CPP file
  for (auto attr : attributeList) {
    if (Method::isa(attr))
      visit(attr);
  }
}

void CPPEmitter::visit(Method *method) { /* do nothing */
  auto argList = method->getInputArgList();
  std::string argsDecl;
  for (auto arg = argList.begin(); arg != argList.end(); arg++) {
    argsDecl += resolveScope((*arg)->getType()) + " " + (*arg)->getId();
    if (arg + 1 != argList.end())
      argsDecl += ", ";
  }
  if (!m_forDef) {
    m_outFile << resolveScope(method->getType())
              << " " + method->getId() + "(" + argsDecl + ");" << std::endl;
  } else {
    if (method->getClass())
      m_outFile << resolveScope(method->getType()) + " " +
                       method->getClass()->getId() + "::" + method->getId() +
                       "(" + argsDecl + ") {"
                << std::endl
                << "}" << std::endl;
    else
      m_outFile << resolveScope(method->getType()) + " " + method->getId() +
                       "(" + argsDecl + ") {"
                << std::endl
                << "}" << std::endl;
  }
}

void CPPEmitter::visit(Variable *variable) {
  // Ex: int m_var;
  m_outFile << resolveScope(variable->getType()) + " m_" + variable->getId() +
                   ";"
            << std::endl;
}

} // namespace UML