#include "TesterUtils.hpp"

std::string CPPEmitterTester::getCPP(UML::Node *node,
                                     UML::CPPEmitter *aCPPEmitter) {
  node->accept(aCPPEmitter);
  return aCPPEmitter->emit<false>();
}