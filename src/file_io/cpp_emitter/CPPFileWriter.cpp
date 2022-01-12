#include "file_io/cpp_emitter/CPPFileWriter.hpp"
#include "core/ClassDecl.hpp"
#include "core/UMLData.hpp"
#include "file_io/cpp_emitter/CPPEmitter.hpp"
#include "file_io/cpp_emitter/TypeHeaderParser.hpp"
#include <fstream>
#include <memory>


namespace UML {

void CPPFileWriter::write(UMLData *p_umlData) {
  auto aCPPEmitter = std::make_unique<CPPEmitter>(p_umlData);
  auto classDecl = dynamic_cast<ClassDecl *>(p_umlData->getNode());

  std::string hppContents = aCPPEmitter->emit<false /*for hpp*/>();

  auto hppFilename = classDecl->getId() + ".hpp";

  std::ofstream outFile;
  outFile.open(hppFilename);
  outFile << hppContents;
  outFile.close();

  HeaderInfo aHeaderInfo = {hppFilename, ""};
  TypeHeaderParser::parseAndGetInfo().insert(
      std::make_pair(classDecl->getId(), aHeaderInfo));

  std::string cppContents = aCPPEmitter->emit<true /*for cpp*/>();

  auto cppFilename = classDecl->getId() + ".cpp";
  outFile.open(cppFilename);
  outFile << cppContents;
  outFile.close();
}
} // namespace UML