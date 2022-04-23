#include "file_io/FileWriter.hpp"
#include "file_io/FormatPref.hpp"
#include "file_io/cpp_emitter/CPPFileWriter.hpp"
#include <memory>

namespace UML {
void FileWriter::write() {
  switch (m_umlContext->getFormatPref()->getLanguage()) {
    case LANG::CPP: {
      CPPFileWriter cppFileWriter;
      cppFileWriter.write(m_umlContext);
    }
  }
}
}  // namespace UML