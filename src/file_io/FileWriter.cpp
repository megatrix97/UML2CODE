#include "file_io/FileWriter.hpp"
#include "file_io/FormatPref.hpp"
#include "file_io/cpp_emitter/CPPFileWriter.hpp"
#include <memory>

namespace UML {

void FileWriter::write(UMLData *umlData) {
  switch (m_formatPref->getLanguage()) {
  case LANG::CPP: {
    CPPFileWriter cppFileWriter;
    cppFileWriter.write(umlData);
    break;
  }
  default:
    break;
  }
}

} // namespace UML