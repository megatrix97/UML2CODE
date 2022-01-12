#ifndef __CPPEMITTER_HPP__
#define __CPPEMITTER_HPP__

#include "CPPEmitterTools.hpp"
#include "core/ClassDecl.hpp"
#include "core/RequiredHeaders.hpp"
#include "core/UMLData.hpp"
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
  UMLData *m_umlData;
  TypeHeaderInfo m_thInfo;
  bool m_forDef =
      false; // flag to switch between emitting declaration and definition

  // private functions
  inline std::string resolveScope(std::string type);

  template <bool forDef> void generateContent(ClassDecl *p_classdecl);
  template <bool forDef> void addRequiredLibraries(ClassDecl *p_classdecl);

public:
  CPPEmitter(UMLData *umlData) : m_umlData(umlData) {
    m_thInfo = TypeHeaderParser::parseAndGetInfo();
  };
  ~CPPEmitter();
  void visit(Node *node) override;
  void visit(ClassDecl *classdecl) override;
  void visit(Variable *variable) override;
  void visit(Method *method) override;
  template <bool forDef> std::string emit() {
    m_forDef = forDef;
    visit(m_umlData->getNode());

    auto strToEmit = m_strStream.str();
    m_strStream.str(std::string());
    return strToEmit;
  }

  friend class CPPEmitterTester;
};

} // namespace UML

#endif