#include "file_io/cpp_emitter/CPPFileWriter.hpp"
#include "core/ClassDecl.hpp"
#include "file_io/cpp_emitter/CPPEmitter.hpp"
#include "file_io/cpp_emitter/TypeHeaderParser.hpp"
#include <fstream>
#include <memory>

namespace UML {

void CPPFileWriter::write(UMLContext *p_umlContext) {
  auto listOfClasses = p_umlContext->getAllClasses();
  auto aCPPEmitter = std::make_unique<CPPEmitter>(p_umlContext);

  for (auto aClass : listOfClasses) {
    std::vector<std::string> filenames =
        p_umlContext->getFilePathDeterminer()->getFilePath(aClass);

    if (filenames.empty()) continue;

    // we assume that each class has both hpp and cpp and proceed further.
    // but it is not necessary
    // TODO : Add check when a class doesn't have one of hpp/cpp

    std::string cppFilename = filenames[0], hppFilename = filenames[1];

    if (cppFilename.compare(cppFilename.size() - 3, 3, "cpp") != 0) {
      // swap the filenames when they are misassigned
      std::string temp = cppFilename;
      cppFilename = hppFilename;
      hppFilename = temp;
    }

    std::string hppContents = aCPPEmitter->emit<false /*for hpp*/>(aClass);
    std::ofstream outFile;
    outFile.open(hppFilename);
    outFile << hppContents;
    outFile.close();

    HeaderInfo aHeaderInfo = {hppFilename, ""};
    p_umlContext->getTypeHeaderInfo()->insert(
        std::make_pair(aClass->getId(), aHeaderInfo));

    std::string cppContents = aCPPEmitter->emit<true /*for cpp*/>(aClass);
    outFile.open(cppFilename);
    outFile << cppContents;
    outFile.close();
  }
}
}  // namespace UML