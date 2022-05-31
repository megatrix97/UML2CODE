#pragma once

#include <iostream>
#include <vector>
#include "ClassDecl.hpp"
#include "utils/RelationshipDataProvider.hpp"
#include "file_io/FilePathDeterminer.hpp"
#include "file_io/FormatPref.hpp"
#include "file_io/cpp_emitter/TypeHeaderParser.hpp"

namespace UML {
class UMLContext {
  std::vector<ClassDecl *> m_allClasses;
  RDP *m_rdpInstance;
  FilePathDeterminer *m_fpdInstance;
  FormatPref *m_formatPref;
  TypeHeaderInfo *m_typeHeaderInfo;

 public:
  UMLContext(std::vector<ClassDecl *> allClasses, RDP *rdpInstance,
             FormatPref *formatPref);
  ~UMLContext();
  std::vector<ClassDecl *> getAllClasses();
  RDP *getRDP();
  FilePathDeterminer *getFilePathDeterminer();
  FormatPref *getFormatPref();
  TypeHeaderInfo *getTypeHeaderInfo();
};
}