#include "file_io/FormatPref.hpp"

namespace UML {
const LANG FormatPref::getLanguage() const { return m_language; }

const INDENTATION FormatPref::getIndentation() const { return m_indentation; }

const std::filesystem::path FormatPref::getDestinationDir() {
  return m_destinationDir;
}

FormatPref* FormatPref::setLanguage(LANG aLanguage) {
  m_language = aLanguage;
  return this;
}

FormatPref* FormatPref::setIndentation(INDENTATION aIndentation) {
  m_indentation = aIndentation;
  return this;
}

FormatPref* FormatPref::setDestinationDir(std::string aDirectory) {
  std::filesystem::path dirPath{aDirectory};
  if (!std::filesystem::exists(dirPath) &&
      !std::filesystem::create_directories(dirPath)) {
    std::cerr << "[FormatPref] cannot create directory : \"" << aDirectory
              << "\"" << std::endl;
  }
  m_destinationDir = dirPath;
  return this;
}
}  // namespace UML