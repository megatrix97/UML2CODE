#include "file_io/cpp_emitter/CPPEmitter.hpp"
#include "core/ClassDecl.hpp"
#include "file_io/EmitterTools.hpp"
#include "file_io/cpp_emitter/TypeHeaderParser.hpp"
#include <memory>
#include <string_view>
#include <utility>

namespace UML {

template <>
void CPPEmitter::generateContent<false>(ClassDecl *p_classdecl) {
  /// generate content to emit .hpp files

  // class declaration
  m_strStream << "class " << p_classdecl->getId();

  if (auto relationshipInfo =
          m_umlContext->getRDP()->getRelationshipData(p_classdecl)) {
    // TODO: Check if every relationship is to be treated as inheritance
    m_strStream << ": public " << relationshipInfo->second->getId();
  }

  m_strStream << " {" << std::endl;

  auto attributeList = p_classdecl->getAttributeList();

  // declare variables first
  for (auto attr : attributeList) {
    if (Variable::isa(attr)) {
      attr->accept(this);

      if (auto accessType = attr->getAccessType()->getType();
          accessType == ACCESS::PRIVATE || accessType == ACCESS::PROTECTED) {
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
  }

  // since we added new attributes, we get the new attributelist again
  attributeList = p_classdecl->getAttributeList();

  auto isMethodOfAccessType = [](Attribute *aAttribute,
                                 ACCESS aAccess) -> bool {
    return Method::isa(aAttribute) &&
           aAttribute->getAccessType()->getType() == aAccess;
  };

  std::vector<Attribute *> publicAttributes, privateAttributes;
  std::copy_if(attributeList.begin(), attributeList.end(),
               std::back_inserter(publicAttributes),
               [isMethodOfAccessType](Attribute *aAttribute) -> bool {
                 return isMethodOfAccessType(aAttribute, ACCESS::PUBLIC);
               });
  std::copy_if(attributeList.begin(), attributeList.end(),
               std::back_inserter(privateAttributes),
               [isMethodOfAccessType](Attribute *aAttribute) -> bool {
                 return isMethodOfAccessType(aAttribute, ACCESS::PRIVATE);
               });

  // declare private methods
  std::for_each(
      privateAttributes.begin(), privateAttributes.end(),
      [this](Attribute *aAttribute) -> void { aAttribute->accept(this); });

  if (!publicAttributes.empty()) {
    m_strStream << "public: " << std::endl;
  }

  // declare public methods
  std::for_each(
      publicAttributes.begin(), publicAttributes.end(),
      [this](Attribute *aAttribute) -> void { aAttribute->accept(this); });

  m_strStream << "}; " << std::endl;
}

template <>
void CPPEmitter::generateContent<true>(ClassDecl *p_classdecl) {
  auto attributeList = p_classdecl->getAttributeList();
  for (auto attr : attributeList) {
    if (Method::isa(attr)) attr->accept(this);
  }
}

template <>
void CPPEmitter::addRequiredLibraries<false>(ClassDecl *p_classdecl) {
  // add header guards
  m_strStream << PRAGMA_ONCE << std::endl;

  // include required libraries
  auto allTypes = p_classdecl->getInvolvedTypes();
  std::unordered_set<std::string> allHeaders;
  for (auto type : allTypes) {
    if (m_typeHeaderInfo->find(type) != m_typeHeaderInfo->end()) {
      allHeaders.insert((*m_typeHeaderInfo)[type].m_headerfile);
    }
  }
  for (auto header : allHeaders) {
    m_strStream << "#include<" << header << ">" << std::endl;
  }
}

template <>
void CPPEmitter::addRequiredLibraries<true>(ClassDecl *p_classdecl) {
  // we only include the .hpp file where class is present.
  // Because, we have already included all other libraries in .hpp already.

  // TODO : Check if it is better to put required libraries in .cpp and
  // just declare them in .hpp
  auto header = m_typeHeaderInfo->find(p_classdecl->getId());
  if (header != m_typeHeaderInfo->end()) {
    m_strStream << "#include \"" << (*header).second.m_headerfile << "\""
                << std::endl;
  }
}

inline std::string CPPEmitter::resolveScope(std::string type) {
  if (m_typeHeaderInfo->find(type) == m_typeHeaderInfo->end()) return type;

  auto nmspc = (*m_typeHeaderInfo)[type].m_namespace;
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
    if (arg + 1 != argList.end()) argsDecl += ", ";
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
}  // namespace UML