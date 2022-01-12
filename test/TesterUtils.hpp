#pragma once
#include "core/Node.hpp"
#include "core/RequiredHeaders.hpp"
#include "file_io/cpp_emitter/CPPEmitter.hpp"

class CPPEmitterTester {
public:
  std::string getCPP(UML::Node *node, UML::CPPEmitter *aCPPEmitter);
};