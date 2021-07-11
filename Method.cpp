#include "Method.hpp"

namespace UML {
void Method::accept(NodeVisitor *visitor) { visitor->visit(this); }
} // namespace UML