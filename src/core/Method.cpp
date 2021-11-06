#include "../../include/core/Method.hpp"

namespace UML {
void Method::accept(NodeVisitor *visitor) { visitor->visit(this); }
bool Method::isa(Node *node) { return dynamic_cast<Method *>(node) != nullptr; }
} // namespace UML