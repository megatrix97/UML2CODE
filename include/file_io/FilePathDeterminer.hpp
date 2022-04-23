#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include "utils/HashGenerator.hpp"

namespace UML {
class ClassDecl;
class FormatPref;
class FilePathDeterminer {
  std::unordered_map<IRUtils::HashKey, std::vector<std::string>> m_filePaths;

  FilePathDeterminer(std::vector<ClassDecl *> allClasses,
                     FormatPref *formatPref) {
    determinePaths(allClasses, formatPref);
  }

  void determinePaths(std::vector<ClassDecl *> allClasses,
                      FormatPref *formatPref);

 public:
  std::vector<std::string> getFilePath(ClassDecl *classDecl);
  friend class UMLContext;
};
}