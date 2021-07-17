#include "include/FileWriter.hpp"
#include "../core/include/ClassDecl.hpp"
#include "cpp_emitter/include/CPPEmitter.hpp"
#include <memory>

namespace UML {

void writeCPP(Node *node, std::shared_ptr<FormatPref> formatPref) {
  if (auto classDecl = dynamic_cast<ClassDecl *>(node)) {
    std::unique_ptr<CPPEmitter> cppEmitter =
        std::make_unique<CPPEmitter>(classDecl->getId() + ".hpp", formatPref);
    cppEmitter->visit(classDecl);
  }
}

void FileWriter::write(Node *node) {
  if (m_formatPref->getLanguage() == LANG::CPP) {
    writeCPP(node, m_formatPref);
  }
}

} // namespace UML