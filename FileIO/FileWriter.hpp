#ifndef __FILEWRITER_HPP__
#define __FILEWRITER_HPP__

#include "../FormatPref.hpp"
#include <fstream>
#include <memory>

namespace UML {
class FileWriter {
  std::ofstream m_file;
  std::shared_ptr<FormatPref> m_emitFormat;

public:
  FileWriter(std::string filename, std::shared_ptr<FormatPref> formatPref)
      : m_emitFormat(formatPref) {
    m_file.open(filename);
  };
  void write();
};
} // namespace UML

#endif