#include "file_io/cpp_emitter/CPPFileWriter.hpp"
#include "core/ClassDecl.hpp"
#include "file_io/cpp_emitter/CPPEmitter.hpp"
#include "file_io/cpp_emitter/TypeHeaderParser.hpp"
#include <filesystem>
#include <fstream>
#include <memory>

namespace UML {

namespace FS = std::filesystem;

void CPPFileWriter::write(UMLContext *p_umlContext) {
  auto listOfClasses = p_umlContext->getAllClasses();
  auto aCPPEmitter = std::make_unique<CPPEmitter>(p_umlContext);

  for (auto aClass : listOfClasses) {
    std::vector<FS::path> filenames =
        p_umlContext->getFilePathDeterminer()->getFilePath(aClass);

    if (filenames.empty()) continue;

    // we assume that each class has both hpp and cpp and proceed further.
    // but it is not necessary
    // TODO : Add check when a class doesn't have one of hpp/cpp

    FS::path cppFilepath = filenames[0], hppFilepath = filenames[1];
    std::string cppFilename = cppFilepath.filename().string(),
                hppFilename = hppFilepath.filename().string();

    if (cppFilename.compare(cppFilename.size() - 4, 4, ".cpp") != 0) {
      // swap the filepaths when they are misassigned
      cppFilepath.swap(hppFilepath);
    }

    FS::path srcDir = cppFilepath.parent_path(),
             incDir = hppFilepath.parent_path();
    if (!FS::exists(srcDir) && !FS::create_directories(srcDir)) {
      std::cerr << "[CPPFileWriter] cannot create directory \"" << srcDir
                << std::endl;
    }
    if (!FS::exists(incDir) && !FS::create_directories(incDir)) {
      std::cerr << "[CPPFileWriter] cannot create directory \"" << incDir
                << std::endl;
    }

    std::string hppContents = aCPPEmitter->emit<false /*for hpp*/>(aClass);
    std::ofstream outFile;
    outFile.open(hppFilepath);
    outFile << hppContents;
    outFile.close();

    HeaderInfo aHeaderInfo = {hppFilename, ""};
    p_umlContext->getTypeHeaderInfo()->insert(
        std::make_pair(aClass->getId(), aHeaderInfo));

    std::string cppContents = aCPPEmitter->emit<true /*for cpp*/>(aClass);
    outFile.open(cppFilepath);
    outFile << cppContents;
    outFile.close();
  }
}
}  // namespace UML