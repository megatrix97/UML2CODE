#ifndef __CPPEMITTER_HPP__
#define __CPPEMITTER_HPP__

#include "../../../core/include/RequiredHeaders.hpp"
#include "../../include/FormatPref.hpp"
#include "CPPEmitterTools.hpp"
#include <fstream>
#include <memory>

namespace UML {
class CPPEmitter : public NodeVisitor {
  std::ofstream m_outFile;
  std::shared_ptr<FormatPref> m_formatPref;
  int indentLevel = 0;

  std::string indent(std::string value);

public:
  CPPEmitter(std::string filename, std::shared_ptr<FormatPref> formatPref)
      : m_formatPref(formatPref) {
    m_outFile.open(filename);
  };
  void visit(Node *node) override;
  void visit(ClassDecl *classdecl) override;
  void visit(Variable *variable) override;
  void visit(Method *method) override;
};
} // namespace UML

#endif