#include "file_io/cpp_emitter/CPPEmitter.hpp"
#include "core/ClassDecl.hpp"
#include "file_io/EmitterTools.hpp"
#include <string_view>
#include <utility>

namespace UML {

constexpr std::string_view PRAGMA_ONCE = "#pragma once";

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

CPPEmitter::~CPPEmitter() {}

void CPPEmitter::prepareToWriteToHpp() {
  // HPP files only contain declarations. Setting flag m_forDef for the emitter
  // to know what to emit.
  m_forDef = false;
}

void CPPEmitter::addRequiredLibraries(ClassDecl *p_classdecl) {
  // Adding header guards
  m_strStream << PRAGMA_ONCE << std::endl;

  // include required libraries
  auto allTypes = p_classdecl->getTypesInvolved();
  for (auto type : allTypes) {
    if (m_umlData->getTypeHeaderInfo().find(type) !=
        m_umlData->getTypeHeaderInfo().end()) {
      m_strStream << "#include<"
                  << m_umlData->getTypeHeaderInfo()[type].m_headerfile << ">"
                  << std::endl;
    }
  }
}

void CPPEmitter::declareClassAndItsAttributes(ClassDecl *p_classdecl) {
  // class declaration
  m_strStream << "class " << p_classdecl->getId() << " {" << std::endl;

  auto attributeList = p_classdecl->getAttributeList();

  // declare variables first
  for (auto attr : attributeList) {
    if (Variable::isa(attr)) {
      attr->accept(this);
      // add getter and setter functions for variable with private and protected
      // access
      auto getMethod =
          new Method(attr->getType(),
                     "get" + EmitterTools::firstLetterToUpper(attr->getId()),
                     {}, ACCESS::PUBLIC);
      getMethod->setClass(p_classdecl);
      auto setMethod = new Method(
          "void", "set" + EmitterTools::firstLetterToUpper(attr->getId()),
          {new Variable(attr->getType(), attr->getId())}, ACCESS::PUBLIC);
      setMethod->setClass(p_classdecl);
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

std::string CPPEmitter::writeToHpp(std::string p_filename_wo_ext) {
  std::string hppFilename = p_filename_wo_ext + ".hpp";
  m_outFile.open(hppFilename);
  m_outFile << m_strStream.str();
  m_outFile.close();
  return hppFilename;
}

void CPPEmitter::prepareToWriteToCpp() { m_forDef = true; }

void CPPEmitter::writeToCpp(std::string p_filename_wo_ext) {
  m_outFile.open(p_filename_wo_ext + ".cpp");
  m_outFile << m_strStream.str();
}

void CPPEmitter::visit(Node *node) { node->accept(this); }

void CPPEmitter::visit(ClassDecl *p_classdecl) {

  prepareToWriteToHpp();
  addRequiredLibraries(p_classdecl);
  declareClassAndItsAttributes(p_classdecl);
  auto hppFilename = writeToHpp(p_classdecl->getId());

  // add header file info for the new class type
  HeaderInfo aHeaderInfo = {"", hppFilename};
  m_umlData->getTypeHeaderInfo().insert(
      std::make_pair(p_classdecl->getId(), aHeaderInfo));

  prepareToWriteToCpp();
  // include required libraries
  // we only include class .hpp file because it contains all the required
  // headers already.
  m_strStream << "#include \"" << p_classdecl->getId() + ".hpp"
              << "\"" << std::endl;
  // writing to CPP file
  auto attributeList = p_classdecl->getAttributeList();
  for (auto attr : attributeList) {
    if (Method::isa(attr))
      attr->accept(this);
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

void CPPEmitter::emit() { visit(m_umlData->getNode()); }

} // namespace UML