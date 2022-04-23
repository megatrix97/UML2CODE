#ifndef __FILEWRITER_HPP__
#define __FILEWRITER_HPP__

#include "FormatPref.hpp"
#include "core/Node.hpp"
#include "core/UMLContext.hpp"

namespace UML {
class FileWriter {
  UMLContext* m_umlContext;

 public:
  FileWriter(UMLContext* umlContext) : m_umlContext(umlContext) {}
  virtual void write();
  virtual ~FileWriter(){};
};
}  // namespace UML

#endif