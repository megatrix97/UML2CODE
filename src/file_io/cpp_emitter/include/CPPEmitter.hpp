#ifndef __CPPEMITTER_HPP__
#define __CPPEMITTER_HPP__

#include "../../../core/include/RequiredHeaders.hpp"
#include "../../../core/include/UMLData.hpp"
#include "../../include/FormatPref.hpp"
#include "CPPEmitterTools.hpp"
#include <fstream>
#include <memory>

namespace UML {
class CPPEmitter : public NodeVisitor {
  std::ofstream m_outFile;
  std::shared_ptr<FormatPref> m_formatPref;
  bool m_forDef; // flag to switch between emitting declaration and definition

public:
  CPPEmitter(std::shared_ptr<FormatPref> formatPref)
      : m_formatPref(formatPref){};
  void emit(UMLData umlData);
  void visit(Node *node) override;
  void visit(ClassDecl *classdecl) override;
  void visit(Variable *variable) override;
  void visit(Method *method) override;
};
} // namespace UML

#endif