#include "core/Variable.hpp"
#include "core/Attribute.hpp"
#include "core/NodeVisitor.hpp"

namespace UML {
InvolvedTypes Variable::getInvolvedTypes() {
  InvolvedTypes it;
  it.push_back(getType());
  return it;
}
bool Variable::isa(Node *node) {
  return dynamic_cast<Variable *>(node) != nullptr;
}
void Variable::accept(NodeVisitor *visitor) { visitor->visit(this); }
}  // namespace UML