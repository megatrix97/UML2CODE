#include "include/FileWriter.hpp"
#include "../core/include/ClassDecl.hpp"
#include "cpp_emitter/include/CPPEmitter.hpp"
#include <memory>

namespace UML {

void writeCPP(UMLData umlData, const std::shared_ptr<FormatPref> formatPref) {

  std::unique_ptr<CPPEmitter> cppEmitter =
      std::make_unique<CPPEmitter>(formatPref);
  cppEmitter->emit(umlData);
}

void FileWriter::write(UMLData umlData) {
  if (m_formatPref->getLanguage() == LANG::CPP) {
    writeCPP(umlData, m_formatPref);
  }
}

} // namespace UML