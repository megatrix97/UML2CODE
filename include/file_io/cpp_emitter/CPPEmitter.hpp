#ifndef __CPPEMITTER_HPP__
#define __CPPEMITTER_HPP__

#include "CPPEmitterTools.hpp"
#include "core/ClassDecl.hpp"
#include "core/RequiredHeaders.hpp"
#include "core/UMLContext.hpp"
#include "file_io/EmitterTools.hpp"
#include "file_io/FormatPref.hpp"
#include "file_io/cpp_emitter/TypeHeaderParser.hpp"
#include <fstream>
#include <memory>
#include <sstream>

namespace UML {
constexpr std::string_view PRAGMA_ONCE = "#pragma once";
class CPPEmitter : public NodeVisitor {
  std::stringstream m_strStream;
  UMLContext *m_umlContext;
  TypeHeaderInfo *m_typeHeaderInfo;
  bool m_forDef =
      false;  // flag to switch between emitting declaration and definition

  // private functions
  inline std::string resolveScope(std::string type);

  template <bool forDef>
  void generateContent(ClassDecl *p_classdecl);
  template <bool forDef>
  void addRequiredLibraries(ClassDecl *p_classdecl);

 public:
  CPPEmitter(UMLContext *umlContext) : m_umlContext(umlContext) {
    m_typeHeaderInfo = umlContext->getTypeHeaderInfo();
  }
  ~CPPEmitter();
  void visit(Node *node) override;
  void visit(ClassDecl *classdecl) override;
  void visit(Variable *variable) override;
  void visit(Method *method) override;
  template <bool forDef>
  std::string emit(ClassDecl *p_classDecl) {
    m_forDef = forDef;
    p_classDecl->accept(this);

    auto strToEmit = m_strStream.str();
    m_strStream.str(std::string());
    return strToEmit;
  }
};

}  // namespace UML

#endif