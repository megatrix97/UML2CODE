#ifndef __CPPEMITTER_HPP__
#define __CPPEMITTER_HPP__

#include "CPPEmitterTools.hpp"
#include "core/RequiredHeaders.hpp"
#include "core/UMLData.hpp"
#include "file_io/FormatPref.hpp"
#include <fstream>
#include <memory>
#include <sstream>

namespace UML {
class CPPEmitter : public NodeVisitor {
  std::ofstream m_outFile;
  std::stringstream m_strStream;
  std::shared_ptr<FormatPref> m_formatPref;
  std::shared_ptr<UMLData> m_umlData;
  bool m_forDef; // flag to switch between emitting declaration and definition

  // private functions
  inline std::string resolveScope(std::string type);

  void prepareToWriteToHpp();
  void addRequiredLibraries(ClassDecl *p_classdecl);
  void declareClassAndItsAttributes(ClassDecl *p_classdecl);
  std::string writeToHpp(std::string p_filename_wo_ext);
  void prepareToWriteToCpp();
  void writeToCpp(std::string p_filename_wo_ext);

public:
  CPPEmitter(std::shared_ptr<FormatPref> formatPref,
             std::shared_ptr<UMLData> umlData)
      : m_formatPref(formatPref), m_umlData(umlData){};
  ~CPPEmitter();
  void visit(Node *node) override;
  void visit(ClassDecl *classdecl) override;
  void visit(Variable *variable) override;
  void visit(Method *method) override;
  void emit();
};
} // namespace UML

#endif