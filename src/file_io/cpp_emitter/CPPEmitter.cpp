#include "file_io/cpp_emitter/CPPEmitter.hpp"
#include "core/ClassDecl.hpp"
#include "file_io/EmitterTools.hpp"
#include "file_io/cpp_emitter/TypeHeaderParser.hpp"
#include <string_view>
#include <utility>

namespace UML {

template <> void CPPEmitter::generateContent<false>(ClassDecl *p_classdecl) {
  // class declaration
  m_strStream << "class " << p_classdecl->getId() << " {" << std::endl;

  auto attributeList = p_classdecl->getAttributeList();

  // declare variables first
  for (auto attr : attributeList) {
    if (Variable::isa(attr)) {
      attr->accept(this);
      // add getter and setter functions for variable with private and
      // protected access
      auto getMethod =
          new Method(attr->getType(),
                     "get" + EmitterTools::firstLetterToUpper(attr->getId()),
                     {}, ACCESS::PUBLIC);
      getMethod->setClass(p_classdecl);
      auto setMethod = new Method(
          "void", "set" + EmitterTools::firstLetterToUpper(attr->getId()),
          {new Variable(attr->getType(), attr->getId())}, ACCESS::PUBLIC);
      setMethod->setClass(p_classdecl);
      p_classdecl->addAttribute(getMethod);
      p_classdecl->addAttribute(setMethod);
    }
  }

  // since we added new attributes, we get the new attributelist again
  attributeList = p_classdecl->getAttributeList();

  auto isMethodOfAccessType = [](Attribute *aAttribute,
                                 ACCESS aAccess) -> bool {
    return Method::isa(aAttribute) && aAttribute->getAccessType() == aAccess;
  };

  // declare private methods
  for (auto attr : attributeList) {
    if (isMethodOfAccessType(attr, ACCESS::PRIVATE))
      attr->accept(this);
  }

  m_strStream << "public: " << std::endl;

  // declare public methods
  for (auto attr : attributeList) {
    if (isMethodOfAccessType(attr, ACCESS::PUBLIC))
      attr->accept(this);
  }

  m_strStream << "}; " << std::endl;
}

template <> void CPPEmitter::generateContent<true>(ClassDecl *p_classdecl) {
  auto attributeList = p_classdecl->getAttributeList();
  for (auto attr : attributeList) {
    if (Method::isa(attr))
      attr->accept(this);
  }
}

template <>
void CPPEmitter::addRequiredLibraries<false>(ClassDecl *p_classdecl) {
  // add header guards
  m_strStream << PRAGMA_ONCE << std::endl;

  // include required libraries
  auto allTypes = p_classdecl->getTypesInvolved();
  for (auto type : allTypes) {
    if (m_thInfo.find(type) != m_thInfo.end()) {
      m_strStream << "#include<" << m_thInfo[type].m_headerfile << ">"
                  << std::endl;
    }
  }
}

template <>
void CPPEmitter::addRequiredLibraries<true>(ClassDecl *p_classdecl) {
  // we only include the .hpp file where class is present.
  // Because, we have already included all other libraries in .hpp already.
  auto header = m_thInfo.find(p_classdecl->getId());
  if (header != m_thInfo.end()) {
    std::cout << "header file: " << (*header).second.m_headerfile
              << ", class: " << (*header).first << std::endl;
    m_strStream << "#include \"" << (*header).second.m_headerfile << "\""
                << std::endl;
  }
}

inline std::string CPPEmitter::resolveScope(std::string type) {
  if (m_thInfo.find(type) == m_thInfo.end())
    return type;

  auto nmspc = m_thInfo[type].m_namespace;
  if (!nmspc.empty()) {
    return nmspc + "::" + type;
  } else
    return type;
}

CPPEmitter::~CPPEmitter() {}

void CPPEmitter::visit(Node *node) { node->accept(this); }

void CPPEmitter::visit(ClassDecl *p_classdecl) {
  if (!m_forDef) {
    addRequiredLibraries<false>(p_classdecl);
    generateContent<false>(p_classdecl);
  } else {
    addRequiredLibraries<true>(p_classdecl);
    generateContent<true>(p_classdecl);
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
    m_strStream << resolveScope(method->getType())
                << " " + method->getId() + "(" + argsDecl + ");" << std::endl;
  } else {
    if (method->getClass())
      m_strStream << resolveScope(method->getType()) + " " +
                         method->getClass()->getId() + "::" + method->getId() +
                         "(" + argsDecl + ") {"
                  << std::endl
                  << "}" << std::endl;
    else
      m_strStream << resolveScope(method->getType()) + " " + method->getId() +
                         "(" + argsDecl + ") {"
                  << std::endl
                  << "}" << std::endl;
  }
}

void CPPEmitter::visit(Variable *variable) {
  // Ex: int m_var;
  m_strStream << resolveScope(variable->getType()) + " m_" + variable->getId() +
                     ";"
              << std::endl;
}
} // namespace UML