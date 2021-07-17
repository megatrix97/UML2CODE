#ifndef __FILEWRITER_HPP__
#define __FILEWRITER_HPP__
#include "../../core/include/Node.hpp"
#include "FormatPref.hpp"
#include <memory>

namespace UML {
class FileWriter {
  std::shared_ptr<FormatPref> m_formatPref;

public:
  FileWriter(std::shared_ptr<FormatPref> formatPref)
      : m_formatPref(formatPref) {}
  void write(Node *node);
};
} // namespace UML

#endif