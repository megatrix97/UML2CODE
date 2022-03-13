#include "core/Method.hpp"

namespace UML {
void Method::setInvolvedTypes() {
  m_typesInvolved.insert(getType());
  for (auto var : getInputArgList()) {
    m_typesInvolved.insert(var->getType());
  }
}
InvolvedTypes Method::getInvolvedTypes() {
  InvolvedTypes involvedTypes(m_typesInvolved.begin(), m_typesInvolved.end());
  return involvedTypes;
}
void Method::accept(NodeVisitor *visitor) { visitor->visit(this); }
bool Method::isa(Node *node) { return dynamic_cast<Method *>(node) != nullptr; }
}  // namespace UML