#include "../../include/core/Variable.hpp"
#include "../../include/core/NodeVisitor.hpp"

namespace UML {
bool Variable::isa(Node *node) {
  return dynamic_cast<Variable *>(node) != nullptr;
}
void Variable::accept(NodeVisitor *visitor) { visitor->visit(this); }
} // namespace UML