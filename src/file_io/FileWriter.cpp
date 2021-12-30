#include "file_io/FileWriter.hpp"
#include "core/ClassDecl.hpp"
#include "file_io/cpp_emitter/CPPEmitter.hpp"
#include <memory>

namespace UML {

void writeCPP(std::shared_ptr<UMLData> umlData,
              const std::shared_ptr<FormatPref> formatPref) {

  std::unique_ptr<CPPEmitter> cppEmitter =
      std::make_unique<CPPEmitter>(formatPref, umlData);
  cppEmitter->emit();
}

void FileWriter::write(std::shared_ptr<UMLData> umlData) {
  if (m_formatPref->getLanguage() == LANG::CPP) {
    writeCPP(umlData, m_formatPref);
  }
}

} // namespace UML