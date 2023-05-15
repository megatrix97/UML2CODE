#include "core/UMLContext.hpp"

namespace UML {
UMLContext::UMLContext(std::vector<ClassDecl*> allClasses, RDP* rdpInstance,
                       FormatPref* formatPref) {
  m_allClasses = allClasses;
  m_rdpInstance = rdpInstance;
  m_formatPref = formatPref;
  m_fpdInstance = new FilePathDeterminer(allClasses, formatPref);
  m_typeHeaderInfo = TypeHeaderParser::parseAndGetInfo();
}

UMLContext::~UMLContext() { delete m_fpdInstance; }

std::vector<ClassDecl*> UMLContext::getAllClasses() { return m_allClasses; }

RDP* UMLContext::getRDP() { return m_rdpInstance; }

FilePathDeterminer* UMLContext::getFilePathDeterminer() {
  return m_fpdInstance;
}

FormatPref* UMLContext::getFormatPref() { return m_formatPref; }

TypeHeaderInfo* UMLContext::getTypeHeaderInfo() { return m_typeHeaderInfo; }
}