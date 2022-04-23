#include "file_io/FilePathDeterminer.hpp"
#include "file_io/FormatPref.hpp"

namespace UML {
void FilePathDeterminer::determinePaths(std::vector<ClassDecl*> allClasses,
                                        FormatPref* formatPref) {
  auto lang = formatPref->getLanguage();
  auto destPath = formatPref->getDestinationDir();
  for (auto cls : allClasses) {
    std::vector<std::string> paths;
    switch (lang) {
      case LANG::CPP:
        paths.push_back(destPath + "/src/" + cls->getId() + ".cpp");
        paths.push_back(destPath + "/include/" + cls->getId() + ".hpp");
        break;
      default:
        break;
    }
    m_filePaths.insert(std::make_pair(IRUtils::generateHash(cls), paths));
  }
}

std::vector<std::string> FilePathDeterminer::getFilePath(
    ClassDecl* p_classDecl) {
  IRUtils::HashKey classHash = IRUtils::generateHash(p_classDecl);
  return m_filePaths.find(classHash) != m_filePaths.end()
             ? m_filePaths[classHash]
             : (std::vector<std::string>());
}
}