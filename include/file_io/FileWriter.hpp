#ifndef __FILEWRITER_HPP__
#define __FILEWRITER_HPP__

#include "FormatPref.hpp"
#include "core/Node.hpp"
#include "core/UMLData.hpp"

namespace UML {
class FileWriter {
  FormatPref *m_formatPref;

public:
  FileWriter(FormatPref *formatPref) : m_formatPref(formatPref) {}
  virtual void write(UMLData *umlData);
  virtual ~FileWriter(){};
};
} // namespace UML

#endif